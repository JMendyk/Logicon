//
// Created by rufus on 12.12.17.
//

#include <iostream>
#include <circuit.h>
#include <gates/and.h>
#include <gates/input.h>
#include <exceptions/logiconException.h>
#include "app.h"

namespace Logicon {

    void infoGate(const std::shared_ptr<Gate> &gate) {
        std::string gateType;
        if (std::dynamic_pointer_cast<Logicon::And>(gate) != nullptr)
            gateType = "AND";
        else if (std::dynamic_pointer_cast<Logicon::Input>(gate) != nullptr)
            gateType = "INPUT";

        std::cout << gateType << "~" << gate->getID() << " ";
        for (Port i = 0; i < gate->getInputsCount(); ++i) {
            std::cout << "I[" << i << "]=(" << gate->getInputState(i) << "){ ";
            auto inputs = gate->getInputConnections(i);
            for (auto &input : inputs)
                std::cout << "#" << input.id << ":" << input.port << "  ";
            std::cout << "} ";
        }
        for (Port i = 0; i < gate->getOutputsCount(); ++i) {
            std::cout << "O[" << i << "]=(" << gate->getOutputState(i) << "){ ";
            auto outputs = gate->getOutputConnections(i);
            for (auto &output : outputs)
                std::cout << "#" << output.id << ":" << output.port << "  ";
            std::cout << "} ";
        }
        std::cout << std::endl;
    }

    void App::run() {
        Circuit circuit(Logicon::Circuit::nextID());
        std::cout << "commands: exit, info, add, connect, disconnect" << std::endl;
        while (true) {
            std::string cmd;
            std::cin >> cmd;
            if (cmd == "exit")
                return;
            else if (cmd == "info") {
                auto gates = circuit.getGates();
                if (gates.empty())
                    std::cout << "circuit is empty" << std::endl;
                else {
                    std::cout << "================" << std::endl;
                    for (const auto &gate : gates)
                        infoGate(gate);
                    std::cout << "================" << std::endl;
                }
            } else if (cmd == "add") {
                std::string type;
                std::cin >> type;
                if (type == "AND") {
                    std::shared_ptr<And> ptr = std::make_shared<And>(Circuit::nextID());
                    circuit.add(std::static_pointer_cast<Gate, And>(ptr));
                }
            } else if (cmd == "remove") {
                ID id;
                std::cin >> id;
                circuit.remove(id);
            } else if (cmd == "connect") {
                try {
                    ID ID1, ID2;
                    Port output, input;
                    std::cin >> ID1 >> output >> ID2 >> input;
                    circuit.connect(ID1, output, ID2, input);
                } catch (std::exception &e) { //TODO fixup, maybe SEH happens ???
                    std::cerr << "APP:\n" << e.what() << ":APP\n";
                }
            } else if (cmd == "disconnect") {
                ID ID1, ID2;
                Port output, input;
                std::cin >> ID1 >> output >> ID2 >> input;
                circuit.disconnect(ID1, output, ID2, input);
            } else if (cmd == "set") {
                ID id;
                Port port;
                bool isInput;
                State state;
                std::cin >> id >> port >> isInput >> state;
                try {
                    auto g = circuit.find(id);
                    if (isInput)
                        g->setInputState(port, state);
                    else
                        g->setOutputState(port, state);
                } catch (Logicon::logiconException &e) {
                    std::cerr << e.what();
                }
            } else if (cmd == "update") {
                ID id;
                std::cin >> id;
                try {
                    auto g = circuit.find(id);
                    g->update();
                } catch (Logicon::logiconException &e) {
                    std::cerr << e.what();
                }
            }
        }
    }
} // namespace Logicon