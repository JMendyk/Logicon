//
// Created by rufus on 12.12.17.
//

#include "engine.h"

namespace Logicon{
    void restart(Circuit c) {
        graph = c.getGates();
        for(shared_ptr<Gate> gate : graph){
            m.insert(std::pair<id, int>(gate.getID(), 0));
        }

        for(shared_ptr<Gate> gate : graph){

            ///finds unplugged inputs
            if(gate.getInputsCount()!=0)
            {
                for(Port port=0; port<gate.getInputsCount(); port++)
                {
                    if(gate.isInputEmpty(port)) gate.setInputState(port,0);
                }
            }

            for(Port port=0; port<gate.getOutputsCount(); port++)
            {
                if(!gate.isOutputEmpty(port))
                {
                    con=gate.PortConnectionList_ &getOutputConnections(port);
                    for(Connection co=con.begin(); co<con.end(); con++)
                        m[co.id]++;
                }
            }
        }

        for (shared_ptr <Gate> gate : graph) {
            if (m[gate.getID()] == 0) {
                q.push(gate.getID());
                gate.update();
            }
        }

        while(q.size() != graf.size()) {
            for (i=0; i<q.size(); i++) {
                id = q[i];
                gates = find(id);
                for(Port port=0; port<gates.getOutputsCount(); port++)
                {
                    if(!gates.isOutputEmpty(port)) {
                        con = gates.PortConnectionList_ & getOutputConnections(port);
                        for (Connection co = con.begin(); co < con.end(); con++) {
                            m[co.id]--;
                            if (m[co.id] == 0) {
                                q.push(co.id);
                                gates1 = find(co.id);
                                gates1.update();
                            }
                        }
                    }
                }
            }
            if(q.size() != graf.size()) {
                for(shared_ptr<Gate> gate : graph){
                    if(m[gate.getID()] != 0)
                    {
                        for(Port port=0; port<gate.getInputsCount(); port++)
                        {
                            if(gate.isInputEmpty(port)) gate.setInputState(port,0);
                        }
                        m[gate.getID()] = 0;
                        for(Port port=0; port<gate.getOutputsCount(); port++)
                        {
                            if(!gate.isOutputEmpty(port)) {
                                con = gate.PortConnectionList_ & getOutputConnections(port);
                                for (Connection co = con.begin(); co < con.end(); con++) {
                                    m[co.id]--;
                                    if (m[co.id] == 0) {
                                        q.push(co.id);
                                        gates1 = find(co.id);
                                        gates1.update();
                                    }
                                }
                            }
                        }
                        gate.update();
                        q.push(gate.getID());
                        break;
                    }
                }
            }
        }
    }

    void calcLogic(Circuit c) {
        for (i=0; i<q.size(); i++) {
            {
                id = q[i];
                gate = find(id);
                gate.update();
            }
        }
    }
} // namespace Logicon