//
// Created by rufus on 12.12.17.
//

#include "app.h"

void run_shell();

int main(int argv, char *args[]) {

    if(argv == 2 && std::string(args[1]) == "shell") {
        run_shell();
    }

    return 0;
}

/*
 * Shell for testing by @T3sT3ro
 */

#include <circuit.h>
#include <gates/and.h>
#include <gates/input.h>
#include <exceptions/logiconException.h>
#include <logger.h>

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
                std::cout << "#~" << output.id << ":" << output.port << "  ";
            std::cout << "} ";
        }
        std::cout << std::endl;
    }

    void run_shell() {
        Logicon::Logger::init("ToosterTest");
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
                ID ID1, ID2;
                Port output, input;
                std::cin >> ID1 >> output >> ID2 >> input;
                circuit.connect(ID1, output, ID2, input);
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
                auto g = circuit.find(id);
                if (g != nullptr) {
                    if (isInput)
                        g->setInputState(port, state);
                    else
                        g->setOutputState(port, state);
                }
            } else if (cmd == "update") {
                ID id;
                std::cin >> id;
                auto g = circuit.find(id);
                if (g != nullptr)
                    g->update();
            } else if (cmd == "reset") {
                ID id;
                std::cin >> id;
                auto g = circuit.find(id);
                if (g != nullptr)
                    g->reset();
            } else if (cmd == "clear") {
                ID id;
                std::cin >> id;
                auto g = circuit.find(id);
                if (g != nullptr)
                    g->clear();
            }
        }
    }
} // namespace Logicon

void run_shell() {
    Logicon::run_shell();
}