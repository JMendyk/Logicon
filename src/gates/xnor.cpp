//
// Created by kralizekmd on 09.01.2018
//

#include "gates/xnor.h"

namespace Logicon {
    Xnor::Xnor(ID id) : Gate(GATE_TYPE::XNOR, id) {}

    void Xnor::update() {
        this->setOutputState(0, !(this->getInputState(0) ^ this->getInputState(1)));
    }
} // namespace Logicon

