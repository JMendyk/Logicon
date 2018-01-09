//
// Created by kralizekmd on 09.01.2018
//

#include "gates/delay.h"

namespace Logicon {
    Delay::Delay(ID id) : Gate(GATE_TYPE::DELAY, id) {
        this->delay=1;
        this->signals.push_back(0);
    }

    void Delay::update() {
        if(this->delay==0) this->setOutputState(0,this->getInputState(0));
        else{
            this->setOutputState(0,this->signals.back());
            this->signals.pop_back();
            this->signals.push_front(this->getInputState(0));
        }
    }

    void Delay::changeSettings(Tick delay) {
        this->delay=delay;
        this->signals.resize(delay,0);
    }
} // namespace Logicon