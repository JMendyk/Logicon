//
// Created by kralizekmd on 09.01.2018
//

#include "gates/clock.h"

namespace Logicon {
    Clock::Clock(ID id) : Gate(GATE_TYPE::CLOCK, id), onPeriod(1), offPeriod(1), phase(0) {}

    void Clock::update() {
        phase++;
        if (phase >= (onPeriod + offPeriod))
            phase -= (onPeriod + offPeriod);
        if (phase < onPeriod)setOutputState(0, 1);
        else setOutputState(0, 0);
    }

    void Clock::changeSettings(Tick onPeriod, Tick offPeriod, Tick phase) {
        this->onPeriod = onPeriod;
        this->offPeriod = offPeriod;
        this->phase = phase % (onPeriod + offPeriod);
    }

    Tick Clock::getOnPeriod() {
        return this->onPeriod;
    }

    Tick Clock::getOffPeriod() {
        return this->offPeriod;
    }

    Tick Clock::getPhase() {
        return this->phase;
    }

} // namespace Logicon