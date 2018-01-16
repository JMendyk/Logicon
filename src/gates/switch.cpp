//
// Created by kralizekmd on 09.01.2018
//

#include "gates/switch.h"

namespace Logicon {
    Switch::Switch(ID id) : Gate(GATE_TYPE::SWITCH_OFF, id) {
    }

    void Switch::update() {
        this->setOutputState(0, gateType == SWITCH_ON ? this->getInputState(0) : 0);
    }

    void Switch::clickAction() {
        gateType = (gateType == SWITCH_ON ? SWITCH_OFF : SWITCH_ON);
    }

    bool Switch::isClicked() const {
        return gateType == SWITCH_ON;
    }

    void Switch::setClicked(bool clicked) {
        gateType = (clicked ? SWITCH_ON : SWITCH_OFF);
    }
} // namespace Logicon