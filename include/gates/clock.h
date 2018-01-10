//
// Created by kralizekmd on 09.01.2018
//

#ifndef LOGICON_CLOCK_H
#define LOGICON_CLOCK_H


#include "gate.h"

namespace Logicon {
    /**
     * @brief Clock gate implementation.
     * INPUTS:  0
     * OUTPUTS: 1
     * It has it's own intervals of ON and OFF time as well as phase given in ticks.
     * Fields onPeriod, offPeriod and phase specify the behavior of clock.
     * Default values are onPeriod = 1, offPeriod = 1, phase = 0
     *
     * With default phase clock starts in state HIGH and maintains it for [onPeriod] ticks. After this it changes
     * it's state to LOW for [offPeriod] ticks. If phase is set, the function representing state is moved to the
     * right on time axis.
     *
     */
    class Clock : public Gate {

    private:
        /// how long in ticks should the ON state be transmitted
        Tick onPeriod;
        /// how long in ticks should the OFF state be transmitted
        Tick offPeriod;
        /// how much in ticks to move the function representing state to the right on time axis
        Tick phase;

    public:
        /// Constructor: default onPeriod=1 offPeriod=1 phase=0
        /// at the beginning the clock is ON
        explicit Clock(ID id);

        /**
         * Changes state of output according to onState, offState and delay
         */
        void update() override;

        /**
         * Changes settings of clock.
         * @param onPeriod new value for onPeriod in Ticks
         * @param offPeriod new value for offPeriod in Ticks
         * @param phase new value for delay in Ticks
         */
        void changeSettings(Tick onPeriod, Tick offPeriod, Tick phase);

        /// get onPeriod
        Tick getOnPeriod();

        /// get offPeriod
        Tick getOffPeriod();

        /// get phase/actual time for clock
        Tick getPhase();
    };
}  // namespace Logicon

#endif //LOGICON_CLOCK_H

