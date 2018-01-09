//
// Created by kralizekmd on 09.01.2018
//

#include "gates/not.h"

namespace Logicon {
    Not::Not(ID id) : Gate(GATE_TYPE::NOT, id) {}

    void Not::update() {
        this->setOutputState(0, !(this->getInputState(0)));
    }
} // namespace Logicon

