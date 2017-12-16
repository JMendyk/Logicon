//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_AND_H
#define LOGICON_AND_H


#include "gate.h"

namespace Logicon {
    /**
     * @brief And gate implementation.
     * INPUTS:  2
     * OUTPUTS: 1
     */
    class And : Gate {

    public:
        explicit And(ID id, Circuit parent);

        /**
         * Behaves like standard and gate - output is true only if both inputs are true
         */
        void update() override;
    };
}  // namespace Logicon

#endif //LOGICON_AND_H
