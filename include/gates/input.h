//
// Created by kralizekmd on 09.01.2018
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

    private:
        /// state of input
        int STATE_FLAG;

    public:
        /// Constructor: default state is LOW
        explicit Input(ID id);

        /**
         * @brief If the state flag is HIGH outputs HIGH, otherwise outputs LOW
         */
        void update() override;

        /**
         * @brief Changes state flag for block when it is `clicked`
         */
        void clickAction() override;

        /**
         * @brief Returns state of input
         * @return state of CLICKED_FLAG
         */
        bool isClicked() const;
    };
} // namespace Logicon

#endif //LOGICON_INPUT_H
