//
// Created by kralizekmd on 09.01.2018
//

#include "gates/input.h"

namespace Logicon {
    Input::Input(ID id) : Gate(GATE_TYPE::INPUT, id), STATE_FLAG(false) {}

    void Input::update() {
        this->setOutputState(0, STATE_FLAG);
    }

    void Input::clickAction() {
        STATE_FLAG ^= 1;
    }

    bool Input::isClicked() const {
        return STATE_FLAG;
    }
} // namespace Logicon