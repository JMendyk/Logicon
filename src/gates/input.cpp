//
// Created by kralizekmd on 09.01.2018
//

#include "gates/input.h"

namespace Logicon {
    Input::Input(ID id) : Gate(GATE_TYPE::INPUT, id) {
        this->flag=0;
    }

    void Input::update() {
        this->setOutputState(0,flag);
    }

    void Input::clickAction() {
        this->flag^=1;
    }
} // namespace Logicon