//
// Created by kralizekmd on 09.01.2018
//

#include "gates/switch.h"

namespace Logicon {
    Switch::Switch(ID id) : Gate(GATE_TYPE::SWITCH, id), STATE_FLAG(false) {
    }

    void Switch::update() {
        this->setOutputState(0, STATE_FLAG ? this->getInputState(0) : 0);
    }

    void Switch::clickAction() {
        STATE_FLAG ^= 1;
    }

    bool Switch::isClicked() const {
        return STATE_FLAG;
    }

    void Switch::setClicked(bool clicked) {
        STATE_FLAG = clicked;
    }
} // namespace Logicon