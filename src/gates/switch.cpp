//
// Created by kralizekmd on 09.01.2018
//

#include "gates/switch.h"

namespace Logicon {
    Switch::Switch(ID id) : Gate(GATE_TYPE::SWITCH, id) {
        this->flag=0;
    }

    void Switch::update() {
        this->setOutputState(0,this->getInputState(0));
    }

    void Switch::clickAction() {
        this->flag^=1;
    }
} // namespace Logicon