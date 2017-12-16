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

    PortState Gate::getInputState(PortIndex index) {
        return 0;
    }

    void Gate::setInputState(PortIndex index, PortState state) {

    }

    Connection Gate::getInputConnection(PortIndex index) {
        return Logicon::Connection();
    }

    void Gate::setInputConnection(PortIndex index, ID otherId, PortIndex otherPort) {

    }

    PortState Gate::getOutputState(PortIndex index) {
        return 0;
    }

    void Gate::setOutputState(PortIndex index, PortState state) {

    }

    void Gate::addOutputConnection(PortIndex index, ID other_id, PortIndex other_port) {

    }

    void Gate::removeOutputConnection(PortIndex index, ID other_id, PortIndex other_port) {

    }

    Gate::PortConnectionsList_ Gate::getOutputConnections(PortIndex index) {
        return Logicon::Gate::PortConnectionsList_();
    }
} // namespace Logicon