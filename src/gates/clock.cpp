//
// Created by rufus on 11.12.17.
//

#include "gates/clock.h"

namespace Logicon {
    Clock::Clock(ID id) : Gate(id, 0, 1) {
    }

    void Clock::update() {

    }

    void Clock::changeSettings(Tick onPeriod, Tick offPeriod, Tick phase) {

    }

} // namespace Logicon