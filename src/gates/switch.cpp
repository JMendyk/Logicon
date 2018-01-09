//
// Created by kralizekmd on 09.01.2018
//

#include "gates/switch.h"

namespace Logicon {
    Switch::Switch(ID id) : Gate(GATE_TYPE::SWITCH, id), SWITCHED_FLAG(false) {
    }

    void Switch::update() {
        this->setOutputState(0, SWITCHED_FLAG ? this->getInputState(0) : 0);
    }

    void Switch::clickAction() {
        SWITCHED_FLAG ^= 1;
    }

    bool Switch::isClicked() const {
        return SWITCHED_FLAG;
    }
} // namespace Logicon