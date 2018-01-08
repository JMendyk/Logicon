//
// Created by kralizekmd on 09.01.2018
//

#include "gates/or.h"

namespace Logicon {
    Or::Or(ID id) : Gate(GATE_TYPE::OR, id) {}

    void Or::update() {
        this->setOutputState(0, this->getInputState(0) | this->getInputState(1));
    }
} // namespace Logicon

