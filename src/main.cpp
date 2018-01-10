//
// Created by rufus on 12.12.17.
//

#include "app.h"

void run_shell();

int main(int argv, char *args[]) {

    if (argv == 2 && std::string(args[1]) == "shell") {
        run_shell();
    }

    return 0;
}

/*
 * Shell for testing by @T3sT3ro
 */

#include <circuit.h>
#include <gates/and.h>
#include <gates/delay.h>
#include <gates/input.h>
#include <gates/nand.h>
#include <gates/nor.h>
#include <gates/not.h>
#include <gates/or.h>
#include <gates/switch.h>
#include <gates/xnor.h>
#include <gates/xor.h>
#include <exceptions/logiconException.h>
#include <logger.h>
#include <engine.h>

namespace Logicon {
    void infoGate(const std::shared_ptr<Gate> &gate) {
        std::string gateType;
        if (gate->gateType == Logicon::AND)
            gateType = "AND";
        else if (gate->gateType == Logicon::INPUT)
            gateType = "INPUT";
        else if (gate->gateType == Logicon::OR)
            gateType = "OR";
        else if (gate->gateType == Logicon::CLOCK)
            gateType = "CLOCK";
        else if (gate->gateType == Logicon::DELAY)
            gateType = "DELAY";
        else if (gate->gateType == Logicon::SWITCH)
            gateType = "SWITCH";
        else if (gate->gateType == Logicon::NOT)
            gateType = "NOT";

        std::cout << gateType << "~" << gate->id << " ";
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
        Engine *engine = Engine::getInstance();
        std::cout
                << "commands: exit, info, add, connect, disconnect, set, update, click, reset, clear, propagate, restart, calculate"
                << std::endl;
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
                    auto ptr = std::make_shared<And>(Circuit::nextID());
                    circuit.add(std::static_pointer_cast<Gate, And>(ptr));
                } else if (type == "INPUT") {
                    auto ptr = std::make_shared<Input>(Circuit::nextID());
                    circuit.add(std::static_pointer_cast<Gate, Input>(ptr));
                } else if (type == "OR") {
                    auto ptr = std::make_shared<Or>(Circuit::nextID());
                    circuit.add(std::static_pointer_cast<Gate, Or>(ptr));
                } else if (type == "CLOCK") {
                    auto ptr = std::make_shared<Clock>(Circuit::nextID());
                    circuit.add(std::static_pointer_cast<Gate, Clock>(ptr));
                } else if (type == "DELAY") {
                    auto ptr = std::make_shared<Delay>(Circuit::nextID());
                    circuit.add(std::static_pointer_cast<Gate, Delay>(ptr));
                } else if (type == "SWITCH") {
                    auto ptr = std::make_shared<Switch>(Circuit::nextID());
                    circuit.add(std::static_pointer_cast<Gate, Switch>(ptr));
                } else if (type == "NOT") {
                    auto ptr = std::make_shared<Not>(Circuit::nextID());
                    circuit.add(std::static_pointer_cast<Gate, Not>(ptr));
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
            } else if (cmd == "click") {
                ID id;
                std::cin >> id;
                auto g = circuit.find(id);
                if (g != nullptr)
                    g->clickAction();
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
            } else if (cmd == "propagate") {
                ID id;
                std::cin >> id;
                auto gates = circuit.find(id);
                engine->propagateSignal(circuit, gates);
            } else if (cmd == "restart") {
                engine->restart(circuit);
            } else if (cmd == "calculate") {
                engine->calcLogic(circuit);
            }
        }
    }
} // namespace Logicon

void run_shell() {
    Logicon::run_shell();
}