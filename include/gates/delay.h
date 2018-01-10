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
        std::list<State> signals;

    public:
        /// Constructor constructs default 1 tick delay and list contains one element equal 0
        explicit Delay(ID id);

        /**
         * @brief Replays input function on output with specified delay
         */
        void update() override;

        /**
         * @brief Changes settings for delay.
         * if new delay is smaller than former the oldest signals are lost
         * If new delay is bigger than former signals LOW will be transmitted for this excess time
         * @param delay new value for delay in Ticks
         */
        void setDelay(Tick delay);

        /**
         * @brief Returns currently set delay of the gate
         * @return delay of this gate
         */
        Tick getDelay();

        /**
         * @brief Returns internal history of signals stored in delay
         * @return list of signals
         */
        const std::list<State> &getDelayList() const;

        /**
         * @brief Sets history in delay to the history passed in delayList.
         * @param delayList internal history as list to be overwritten
         */
        void setDelayList(const std::list<State> &delayList);

    };
} // namespace Logicon

#endif //LOGICON_DELAY_H

