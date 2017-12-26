//
// Created by rufus on 12.12.17.
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
    class Delay : Gate {

    private:
        /// how much the input signal is shifted into the future. can't be less than 0.
        Tick delay;

    public:
        /// Constructor constructs default 1 tick delay
        explicit Delay(ID id);

        /**
         * Replays input function on output with specified delay
         */
        void update() override;

        /**
         * Changes settings for delay.
         * @param delay new value for delay in Ticks
         */
        void changeSettings(Tick delay);
    };
} // namespace Logicon

#endif //LOGICON_DELAY_H
