//
// Created by kralizekmd on 09.01.2018
//

#include "gates/nand.h"

namespace Logicon {
    Nand::Nand(ID id) : Gate(GATE_TYPE::NAND, id) {}

    void Nand::update() {
        this->setOutputState(0, !(this->getInputState(0) & this->getInputState(1)));
    }
} // namespace Logicon
