//
// Created by kralizekmd on 09.01.2018
//

#ifndef LOGICON_NOT_H
#define LOGICON_NOT_H


#include "gate.h"

namespace Logicon {
    /**
     * @brief Not gate implementation.
     * INPUTS:  1
     * OUTPUTS: 1
     */
    class Not : public Gate {

    public:
        /// Constructor
        explicit Not(ID id);

        /**
         * Behaves like standard not gate - output is true only if input is false
         */
        void update() override;
    };
}  // namespace Logicon


#endif //LOGICON_NOT_H
