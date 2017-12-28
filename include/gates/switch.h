//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_SWITCH_H
#define LOGICON_SWITCH_H


#include "gate.h"

namespace Logicon{
    /**
     * @brief Switch gate implementation
     * Gate works on the same principle as light switch - if it is switched, it sends input to output,
     * if it isn't, then the output is LOW
     */
    class Switch : public Gate {

    public:
        /// Constructor: default state is LOW
        explicit Switch(ID id);

        /**
         * OUT = IN if switched, LOW otherwise
         */
        void update() override;

        /**
         * Changes state on `click` between switched and not switched
         */
        void clickAction() override;

    };
} // namespace Logicon

#endif //LOGICON_SWITCH_H
