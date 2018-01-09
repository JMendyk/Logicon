//
// Created by kralizekmd on 09.01.2018
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

    private:
        /// switch state
        bool SWITCHED_FLAG;

    public:
        /// Constructor: default state is LOW
        explicit Switch(ID id);

        /**
         * @brief OUT = IN if switched, LOW otherwise
         */
        void update() override;

        /**
         * @brief Changes state on `click` between switched and not switched
         */
        void clickAction() override;

        /**
         * @brief Returns true if the switch is ON, false otherwise
         * @return SWITCHED_FLAG
         */
        bool isClicked() const;

    };
} // namespace Logicon

#endif //LOGICON_SWITCH_H
