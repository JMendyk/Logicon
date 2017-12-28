//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_INPUT_H
#define LOGICON_INPUT_H


#include "gate.h"

namespace Logicon {
    /**
     * @brief Input switch gate implementation.
     * INPUTS:  0
     * OUTPUTS: 1
     *
     * Input changes it's state if it is `clicked`.
     * Default state is LOW
     */
    class Input : public Gate {

    public:
        /// Constructor: default state is LOW
        explicit Input(ID id);

        /**
         * If the state flag is HIGH outputs HIGH, otherwise outputs LOW
         */
        void update() override;

        /**
         * Changes state flag for block when it is `clicked`
         */
        void clickAction() override;
    };
} // namespace Logicon

#endif //LOGICON_INPUT_H
