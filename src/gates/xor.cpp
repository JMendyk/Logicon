//
// Created by kralizekmd on 09.01.2018
//

#include "gates/xor.h"

namespace Logicon {
    Xor::Xor(ID id) : Gate(GATE_TYPE::XOR, id) {}

    void Xor::update() {
        this->setOutputState(0, this->getInputState(0) ^ this->getInputState(1));
    }
} // namespace Logicon

