//
// Created by inverb on 10.01.18.
//

#include "engine.h"

namespace Logicon{

    Engine::Engine() :  i(0) {
    con.clear();
    q.clear();
    }

    void Engine::propagateSignal(Circuit c, std::shared_ptr<Gate> gate){
        for(Port port=0; port<gate->getOutputsCount(); port++)
        {
            if(!gate->isOutputEmpty(port)) {
                con = gate->getOutputConnections(port);
                for(int j=0; j<con.size(); j++) {
                    Connection co = con[j];
                    auto gates1 = c.find(co.id);
                    gates1->setInputState(co.port, gate->getOutputState(port));
                }
            }
        }
    }

    void Engine::restart(Circuit c) {
        i=0;
        q.clear();
        graph = c.getGates();
        for(auto gate : graph){
            m.insert(std::pair<ID, int>(gate->getId(), 0));
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

            ///counts plugged inputs
            for(Port port=0; port<gate->getOutputsCount(); port++)
            {
                if(!gate->isOutputEmpty(port))
                {
                    con=gate->getOutputConnections(port);
                    for(int j=0; j<con.size(); j++) {
                        Connection co = con[j];
                        m[co.id]++;
                    }
                }
            }
        }


        ///Algorithm finding proper order of updating

        for (std::shared_ptr <Gate> gate : graph) {
            if (m[gate->getId()] == 0)
                q.push_back(gate->getId());
        }

        while(q.size() != graph.size() || i<q.size()) {
            for ( ; i<q.size(); i++) {
                ID id = q[i];
                auto gates = c.find(id);
                gates->update();
                this->propagateSignal(c, gates);
                for(Port port=0; port<gates->getOutputsCount(); port++)
                {
                    if(!gates->isOutputEmpty(port)) {
                        con = gates->getOutputConnections(port);
                        for(int j=0; j<con.size(); j++) {
                            Connection co = con[j];
                            auto gates1 = c.find(co.id);
                            m[co.id]--;
                            if (m[co.id] == 0)
                                q.push_back(co.id);
                        }
                    }
                }
            }
            if(q.size() != graph.size()) {
                for(std::shared_ptr<Gate> gate : graph){
                    if(m[gate->getId()] != 0)
                    {
                        for(Port port=0; port<gate->getInputsCount(); port++)
                        {
                            if(gate->getInputState(port) != 1) gate->setInputState(port,0);
                        }
                        m[gate->getId()] = 0;
                        q.push_back(gate->getId());
                        break;
                    }
                }
            }
        }
    }

    void Engine::calcTree(Circuit c) {
        i=0;
        q.clear();
        graph = c.getGates();
        for(auto gate : graph){
            m.insert(std::pair<ID, int>(gate->getId(), 0));
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

            ///counts plugged inputs
            for(Port port=0; port<gate->getOutputsCount(); port++)
            {
                if(!gate->isOutputEmpty(port))
                {
                    con=gate->getOutputConnections(port);
                    for(int j=0; j<con.size(); j++) {
                        Connection co = con[j];
                        m[co.id]++;
                    }
                }
            }
        }


        ///Algorithm finding proper order of updating

        for (std::shared_ptr <Gate> gate : graph) {
            if (m[gate->getId()] == 0)
                q.push_back(gate->getId());
        }

        while(q.size() != graph.size() || i<q.size()) {
            for ( ; i<q.size(); i++) {
                ID id = q[i];
                auto gates = c.find(id);
                for(Port port=0; port<gates->getOutputsCount(); port++)
                {
                    if(!gates->isOutputEmpty(port)) {
                        con = gates->getOutputConnections(port);
                        for(int j=0; j<con.size(); j++) {
                            Connection co = con[j];
                            m[co.id]--;
                            if (m[co.id] == 0)
                                q.push_back(co.id);
                        }
                    }
                }
            }
            if(q.size() != graph.size()) {
                for(std::shared_ptr<Gate> gate : graph){
                    if(m[gate->getId()] != 0)
                    {
                        m[gate->getId()] = 0;
                        q.push_back(gate->getId());
                        break;
                    }
                }
            }
        }
    }

    void Engine::calcLogic(Circuit c) {
        i=0;
        for ( ; i<q.size(); i++) {
            {
                ID id = q[i];
                auto gates = c.find(id);
                gates->update();
            }
        }
        i=0;
        for ( ; i<q.size(); i++) {
            {
                ID id = q[i];
                auto gates = c.find(id);
                this->propagateSignal(c, gates);
            }
        }
    }

} // namespace Logicon