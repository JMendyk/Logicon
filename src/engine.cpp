//
// Created by rufus on 12.12.17.
//

#include "engine.h"

namespace Logicon{
    void Engine::restart(Circuit c) {
        graph = c.getGates();
        for(auto gate : graph){
            m.insert(std::pair<ID, int>(gate->getID(), 0));
        }

        for(std::shared_ptr<Gate> gate : graph){

            ///finds unplugged inputs
            if(gate->getInputsCount()!=0)
            {
                for(Port port=0; port<gate->getInputsCount(); port++)
                {
                    if(gate->isInputEmpty(port)) gate->setInputState(port,0);
                }
            }

            for(Port port=0; port<gate->getOutputsCount(); port++)
            {
                if(!gate->isOutputEmpty(port))
                {
                    con=gate->getOutputConnections(port);
                    for(int i=0; i<con.size(); i++) {
                        co = con[i];
                        m[co.id]++;
                    }
                }
            }
        }

        for (std::shared_ptr <Gate> gate : graph) {
            if (m[gate->getID()] == 0) {
                q.push_back(gate->getID());
                gate->update();
                for(Port port=0; port<gate->getOutputsCount(); port++){
                    con=gate->getOutputConnections(port);
                    for(int i=0; i<con.size(); i++) {
                        co = con[i];
                        m[co.id]--;
                    }
                }
            }
        }

        while(q.size() != graph.size()) {
            for (i=0; i<q.size(); i++) {
                id = q[i];
                auto gates = c.find(id);
                for(Port port=0; port<gates->getOutputsCount(); port++)
                {
                    if(!gates->isOutputEmpty(port)) {
                        con = gates->getOutputConnections(port);
                        for(int i=0; i<con.size(); i++) {
                            co = con[i];
                            m[co.id]--;
                            if (m[co.id] == 0) {
                                q.push_back(co.id);
                                auto gates1 = c.find(co.id);
                                gates1->update();
                            }
                        }
                    }
                }
            }
            if(q.size() != graph.size()) {
                for(std::shared_ptr<Gate> gate : graph){
                    if(m[gate->getID()] != 0)
                    {
                        for(Port port=0; port<gate->getInputsCount(); port++)
                        {
                            if(gate->isInputEmpty(port)) gate->setInputState(port,0);
                        }
                        m[gate->getID()] = 0;
                        for(Port port=0; port<gate->getOutputsCount(); port++)
                        {
                            if(!gate->isOutputEmpty(port)) {
                                con = gate->getOutputConnections(port);
                                for(int i=0; i<con.size(); i++) {
                                    co = con[i];
                                    m[co.id]--;
                                    if (m[co.id] == 0) {
                                        q.push_back(co.id);
                                        auto gates1 = c.find(co.id);
                                        gates1->update();
                                    }
                                }
                            }
                        }
                        gate->update();
                        q.push_back(gate->getID());
                        break;
                    }
                }
            }
        }
    }

    void Engine::calcTree(Circuit c) {

        //TODO
    }

    void Engine::calcLogic(Circuit c) {
        for (i=0; i<q.size(); i++) {
            {
                id = q[i];
                auto gate = c.find(id);
                gate->update();
            }
        }
    }
} // namespace Logicon