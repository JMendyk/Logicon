//
// Created by rufus on 11.12.17.
//

#include "data.h"
#include "gui/gCircuit.h"
#include <fstream>
#include <gates/not.h>
#include <gates/delay.h>
#include <gates/switch.h>
#include <gates/and.h>
#include <gates/or.h>
#include <gates/xor.h>
#include <gates/nand.h>
#include <gates/nor.h>
#include <gates/xnor.h>
#include <gates/clock.h>
#include <gates/input.h>

namespace Logicon{
    void Data::save(std::string path, std::shared_ptr<GCircuit> gCircuit) {
        const std::shared_ptr<Circuit> circuit = gCircuit->getCircuit();
        nlohmann::json j_gates = nlohmann::json::array();
        for (auto Gate : circuit->getGates()) {
            auto pos = gCircuit->getGBlockByID(Gate->id)->getPosition();
            nlohmann::json j_gate = {{"id",      Gate->id},
                                     {"x",       pos.x},
                                     {"y",       pos.y},
                                     {"type",    Gate->getGateType()},
                                     {"in_cnt",  Gate->getInputsCount()},
                                     {"out_cnt", Gate->getOutputsCount()}};
            j_gates += j_gate;
        }
        nlohmann::json j_circuit = {{"flag", circuit->INITIALIZED_FLAG},
                                    {"id",   circuit->getId()},
                                    {"list", j_gates}};

        std::ofstream file(path);
        if (file.is_open()) {
            file << j_circuit;
            file.close();
        }
    }

    std::shared_ptr<GCircuit> Data::read(std::string path) {
        std::ifstream my_file(path);
        nlohmann::json j;
        j << my_file;
        std::shared_ptr<Circuit> circuit = std::make_shared<Circuit>(j.value("id", 0));
        std::shared_ptr<GCircuit> gCircuit = std::make_shared<GCircuit>(circuit);
        circuit->INITIALIZED_FLAG = j.value("flag", 0);
        nlohmann::json arr = j["list"];
        std::cout << arr << std::endl;
        std::cout.flush();
        for (int i = 0; i < arr.size(); i++) {
            nlohmann::json j_gate = arr[i];
            std::cout << j_gate;
            std::cout.flush();
            std::shared_ptr<Gate> gate;
            GATE_TYPE type = (GATE_TYPE) (j_gate.value("type", -1));
            ID id = j_gate.value("id", 1);
            UI::Vec2 pos = UI::Vec2(j_gate.value("x", 1), j_gate.value("y", 1));
            switch (type) {
                case NOT:
                    gate = std::make_shared<Not>(id);
                    break;
                case DELAY:
                    gate = std::make_shared<Delay>(id);
                    break;
                case SWITCH_ON:
                    gate = std::make_shared<Switch>(id);
                    break;
                case SWITCH_OFF:
                    gate = std::make_shared<Switch>(id);
                    break;
                case AND:
                    gate = std::make_shared<And>(id);
                    break;
                case OR:
                    gate = std::make_shared<Or>(id);
                    break;
                case XOR:
                    gate = std::make_shared<Xor>(id);
                    break;
                case NAND:
                    gate = std::make_shared<Nand>(id);
                    break;
                case NOR:
                    gate = std::make_shared<Nor>(id);
                    break;
                case XNOR:
                    gate = std::make_shared<Xnor>(id);
                    break;
                case CLOCK:
                    gate = std::make_shared<Clock>(id);
                    break;
                case INPUT_ON:
                    gate = std::make_shared<Input>(id);
                    break;
                case INPUT_OFF:
                    gate = std::make_shared<Input>(id);
                    break;
            }
            circuit->add(gate);
            gCircuit->insert(gate, pos);
        }
        return gCircuit;
    }

} // namespace Logicon