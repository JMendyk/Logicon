//
// Created by rufus on 11.12.17.
//

#include "gates/and.h"

namespace Logicon {
    And::And(ID id) : Gate(GATE_TYPE::AND, id) {}

    void And::update() {
        this->setOutputState(0, this->getInputState(0) & this->getInputState(1));
    }
} // namespace Logicon

