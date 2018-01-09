//
// Created by kralizekmd on 09.01.2018
//

#include "gates/nor.h"

namespace Logicon {
    Nor::Nor(ID id) : Gate(GATE_TYPE::NOR, id) {}

    void Nor::update() {
        this->setOutputState(0, !(this->getInputState(0) | this->getInputState(1)));
    }
} // namespace Logicon

