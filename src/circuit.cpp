//
// Created by Tooster on 16.12.2017.
//

#include <exceptions/wrongPortException.h>
#include <exceptions/idNotFoundException.h>
#include <algorithm>
#include <iostream>
#include <logger.h>
#include "circuit.h"

namespace Logicon {

    Circuit::Circuit(ID id) : id(id) {
        gates.clear();
    }

    ID Circuit::currentId = 0;

    Logicon::ID Circuit::nextID() {
        return currentId++;
    }

    void Circuit::connect(ID idFrom, Port output, ID idTo, Port input) {

        try {
            auto gateFrom = this->find(idFrom);
            auto gateTo = this->find(idTo);

            // if gates not found - throw idNotFoundException
            if (gateFrom == nullptr)
                throw Logicon::idNotFoundException(idFrom);
            if (gateTo == nullptr)
                throw Logicon::idNotFoundException(idTo);

            // if ports are not found - throw wrongPortException
            if (output < 0 || output >= gateFrom->getOutputsCount())
                throw wrongPortException(idFrom, output, false);
            if (input < 0 || input >= gateTo->getInputsCount())
                throw wrongPortException(idTo, input, true);

            bool ConnectedAB = gateFrom->isOutputConnectedWith(output, idTo, input);
            bool ConnectedBA = gateTo->isInputConnectedWith(input, idFrom, output);
            if (ConnectedAB && ConnectedBA)
                Logicon::Logger::info("Tried connecting already connected gates '%d:%d' -> '%d:%d'!",
                                      idFrom, output, idTo, input);
            else if (!ConnectedAB && !ConnectedBA) { // create new connection - override input, add to output
                gateFrom->addOutputConnection(output, idTo, input);
                gateTo->setInputConnection(input, idFrom, output);
            } else // TODO #1 fix windows SEH problems on rethrow
                throw Logicon::logiconException("Information about connection isn't present in both gates!");
        } catch (Logicon::logiconException &e) {
            std::string circumstances = "While connecting blocks '" +
                                        std::to_string(idFrom) + ":" + std::to_string(output) +
                                        "' -> '" +
                                        std::to_string(idTo) + ":" + std::to_string(input) +
                                        "'.";
            e.when(circumstances);
            Logicon::Logger::warn(e.what());
        }
    }

    void Circuit::disconnect(ID idFrom, Port output, ID idTo, Port input) {
        try {
            // might produce exception of gate not found by ID
            auto gateFrom = this->find(idFrom);
            auto gateTo = this->find(idTo);

            // if gates not found - throw idNotFoundException
            if (gateFrom == nullptr)
                throw Logicon::idNotFoundException(idFrom);
            if (gateTo == nullptr)
                throw Logicon::idNotFoundException(idTo);

            // cancel if one of ports is invalid
            if (output < 0 || output >= gateFrom->getOutputsCount())
                throw Logicon::wrongPortException(idFrom, output, false);
            if (input < 0 || input >= gateTo->getInputsCount())
                throw Logicon::wrongPortException(idTo, input, true);

            bool ConnectedAB = gateFrom->isOutputConnectedWith(output, idTo, input);
            bool ConnectedBA = gateTo->isInputConnectedWith(input, idFrom, output);
            if (!ConnectedAB && !ConnectedBA)
                Logicon::Logger::info("Tried disconnecting already disconnected gates '%d:%d' -> '%d:%d'!",
                                      idFrom, output, idTo, input);
            else if (ConnectedAB && ConnectedBA) { // create new connection - override input, add to output
                gateFrom->removeOutputConnection(output, idTo, input);
                gateTo->clearInputConnections(input);
            } else
                throw Logicon::logiconException("Information about connection isn't present in both gates!");
        } catch (Logicon::logiconException &e) {
            std::string circumstances = "While disconnecting blocks '" +
                                        std::to_string(idFrom) + ":" + std::to_string(output) +
                                        "' -> '" +
                                        std::to_string(idTo) + ":" + std::to_string(input) +
                                        "'.";
            e.when(circumstances);
            Logicon::Logger::warn(e.what());
        }
    }

    void Circuit::add(std::shared_ptr<Gate> gate) {
        try {
            if (gates.count(gate->getID()) > 0)
                throw logiconException("Gates with the same ID cannot be in the same circuit!");
            gates.insert(std::pair<ID, std::shared_ptr<Gate>>(gate->getID(), gate));
        } catch (Logicon::logiconException &e) { // TODO #1
            std::string circumstances = "While adding gate with ID:'"
                                        + std::to_string(gate->getID())
                                        + "'.";
            e.when(circumstances);
            Logicon::Logger::warn(e.what());
        }
    }

    void Circuit::remove(ID id) {
        if (gates.count(id) == 0) { // cannot find => abort
            Logicon::Logger::info("Tried removing missing gate with ID:'%d'!", id);
            return;
        }
        auto erased = this->find(id);
        try {
            // erase input connections
            for (Port port = 0; port < erased->getInputsCount(); ++port) { // for all input ports
                auto inputConnections = erased->getInputConnections(port);
                for (auto connection : inputConnections) { // for all input connections at given port
                    auto connected = this->find(connection.id); // connection with other block
                    connected->removeOutputConnection(connection.port, erased->getID(), port); // remove from other
                }
            }
            // erase output connections
            for (Port port = 0; port < erased->getOutputsCount(); ++port) { // for all outputs
                auto outputsConnections = erased->getOutputConnections(port);
                for (auto connection : outputsConnections) { // for all output connections at given port
                    auto connected = this->find(connection.id); // find specified connection
                    connected->clearInputConnections(connection.port); // remove this from the other end
                }
            }
            //remove this
            gates.erase(id);
        } catch (wrongPortException &e) { // TODO #1
            std::string circumstances = "While removing gate with ID:'" +
                                        std::to_string(id) + "' from the circuit.";
            e.when(circumstances);
            Logicon::Logger::warn(e.what());
        }
    }

    std::shared_ptr<Gate> Circuit::find(ID id) {
        auto it = gates.find(id);
        if (it == gates.end())
            return nullptr;
        return it->second;
    }

    std::list<std::shared_ptr<Gate>> Circuit::getGates() {
        std::list<std::shared_ptr<Gate>> gatesList;

        // constructs list from map
        std::transform(gates.begin(),
                       gates.end(),
                       std::back_inserter(gatesList),
                       [](const std::map<ID, std::shared_ptr<Gate>>::value_type &entry) { return entry.second; });

        return gatesList;
    }

} // namespace Logicon