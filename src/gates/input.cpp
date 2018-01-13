//
// Created by kralizekmd on 09.01.2018
//

#include "gates/input.h"

namespace Logicon {
    Input::Input(ID id) : Gate(GATE_TYPE::INPUT_OFF, id) {}

    void Input::update() {
        this->setOutputState(0, gateType == INPUT_ON);
    }

    void Input::clickAction() {
        gateType = (gateType == INPUT_ON ? INPUT_OFF : INPUT_ON);
    }

    bool Input::isClicked() const {
        return gateType == INPUT_ON;
    }

    void Input::setClicked(bool clicked) {
        gateType = (gateType == INPUT_ON ? INPUT_OFF : INPUT_ON);
    }
} // namespace Logicon