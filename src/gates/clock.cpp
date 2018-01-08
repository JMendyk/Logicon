//
// Created by rufus on 11.12.17.
//

#include "gates/clock.h"

namespace Logicon {
    Clock::Clock(ID id) : Gate(GATE_TYPE::CLOCK, id) {
    }

    void Clock::update() {

    }

    void Clock::changeSettings(Tick onPeriod, Tick offPeriod, Tick phase) {

    }

} // namespace Logicon