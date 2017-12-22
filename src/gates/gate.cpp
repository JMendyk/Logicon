//
// Created by rufus on 11.12.17.
//

#include "gates/gate.h"

namespace Logicon {
    Gate::Gate(ID id, Circuit parent) {

    }

    ID Gate::getID() const {
        return 0;
    }

    PortState Gate::getInputState(Port index) {
        return 0;
    }

    void Gate::setInputState(Port index, PortState state) {

    }

    Connection Gate::getInputConnection(Port index) {
        return Logicon::Connection();
    }

    void Gate::setInputConnection(Port index, ID otherId, Port otherPort) {

    }

    PortState Gate::getOutputState(Port index) {
        return 0;
    }

    void Gate::setOutputState(Port index, PortState state) {

    }

    void Gate::addOutputConnection(Port index, ID other_id, Port other_port) {

    }

    void Gate::removeOutputConnection(Port index, ID other_id, Port other_port) {

    }

    Gate::PortConnectionsList_ Gate::getOutputConnections(Port index) {
        return Logicon::Gate::PortConnectionsList_();
    }
} // namespace Logicon