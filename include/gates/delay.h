//
// Created by kralizekmd on 09.01.2018
//

#ifndef LOGICON_DELAY_H
#define LOGICON_DELAY_H


#include "gate.h"

namespace Logicon {
    /**
     * @brief Delay gate implementation.
     * INPUTS:  1
     * OUTPUTS: 1
     * Delay remembers input function and replays it on the output with specified delay in ticks.
     * Default value for delay is 1.
     * Delay can't be less than 0. Can be equal 0, but then it works like any normal cable
     *
     * Function representing state of output in time is something like this:
     * out_state(time+delay) = in_state(time)
     */
    class Delay : public Gate {

    private:
        /// how much the input signal is shifted into the future. can't be less than 0.
        Tick delay;
        /// list of waiting signals
        std::list<int> signals;

    public:
        /// Constructor constructs default 1 tick delay and list contains one element equal 0
        explicit Delay(ID id);

        /**
         * Replays input function on output with specified delay
         */
        void update() override;

        /**
         * Changes settings for delay.
         * if new delay is smaller the oldest signals are lost
         * @param delay new value for delay in Ticks
         */
        void changeSettings(Tick delay);
    };
} // namespace Logicon

#endif //LOGICON_DELAY_H
