//
// Created by rufus on 12.12.17.
//

#include "gates/delay.h"

namespace Logicon {
    Delay::Delay(ID id) : Gate(GATE_TYPE::DELAY, id) {}


    void Delay::update() {

    }

    void Delay::changeSettings(Tick delay) {

    }
} // namespace Logicon