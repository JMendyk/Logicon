//
// Created by kralizekmd on 09.01.2018
//

#include "gates/clock.h"

namespace Logicon {
    Clock::Clock(ID id) : Gate(GATE_TYPE::CLOCK, id) {
        this->onPeriod=1;
        this->offPeriod=1;
        this->phase=0;
    }

    void Clock::update() {
        this->phase++;
        if(this->phase>=(this->onPeriod+this->offPeriod)) this->phase-=(this->onPeriod+this->offPeriod);
        if(this->phase<this->onPeriod) this->setOutputState(0,1);
        else this->setOutputState(0,0);
    }

    void Clock::changeSettings(Tick onPeriod, Tick offPeriod, Tick phase) {
        this->onPeriod=onPeriod;
        this->offPeriod=offPeriod;
        this->phase=phase%(onPeriod+offPeriod);
    }

} // namespace Logicon