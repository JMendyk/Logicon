//
// Created by Tooster on 16.12.2017.
//

#include <exceptions/wrongPortException.h>
#include <exceptions/idNotFoundException.h>
#include <algorithm>
#include <iostream>
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
            if (ConnectedAB && ConnectedBA) // TODO log connection abort - it already exists
                return;
            else if (!ConnectedAB && !ConnectedBA) { // create new connection - override input, add to output
                gateFrom->addOutputConnection(output, idTo, input);
                gateTo->setInputConnection(input, idFrom, output);
            } else // TODO pass ID:port to exception
                throw Logicon::logiconException("Information about connection isn't present in both gates!");
        } catch (Logicon::logiconException &e) { // TODO log
            std::string circumstances = "while connecting blocks '" +
                                        std::to_string(idFrom) + ":" + std::to_string(output) +
                                        "' -> '" +
                                        std::to_string(idTo) + ":" + std::to_string(input) +
                                        "':\n";
            e.when(circumstances);
            std::cerr << e.what(); // TODO fix windows SEH problems on rethrow
            return;
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
            if (!ConnectedAB && !ConnectedBA) // TODO log connection abort - it already exists
                return;
            else if (ConnectedAB && ConnectedBA) { // create new connection - override input, add to output
                gateFrom->removeOutputConnection(output, idTo, input);
                gateTo->clearInputConnections(input);
            } else // TODO pass ID:port to exception
                throw Logicon::logiconException("Information about connection isn't present in both gates!");
        } catch (Logicon::logiconException &e) { // TODO log
            std::string circumstances = "while disconnecting blocks '" +
                                        std::to_string(idFrom) + ":" + std::to_string(output) +
                                        "' -> '" +
                                        std::to_string(idTo) + ":" + std::to_string(input) +
                                        "':\n";
            e.when(circumstances);
            std::cerr << e.what(); // TODO fix windows SEH problems on rethrow
            return;
        }
    }

    void Circuit::add(std::shared_ptr<Gate> gate) {
        if (gates.count(gate->getID()) > 0)
            throw logiconException("Gates with the same ID cannot be in the same circuit!");
        gates.insert(std::pair<ID, std::shared_ptr<Gate>>(gate->getID(), gate));
    }

    void Circuit::remove(ID id) {
        if (gates.count(id) == 0)
            return; // TODO log abort removing nonexistent gate
        auto erased = gates[id];
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
        } catch (wrongPortException &e) {
            std::string circumstances = "Error while removing gate with ID:`" +
                                        std::to_string(id) + "` from circuit.";
            e.when(circumstances);
            std::cerr << e.what(); // TODO fix windows SEH problems on rethrow
            return;
        }

        gates.erase(id);
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