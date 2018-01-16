//
// Created by kralizekmd on 09.01.2018
//

#ifndef LOGICON_OR_H
#define LOGICON_OR_H


#include "gate.h"

namespace Logicon {
    /**
     * @brief Or gate implementation.
     * INPUTS:  2
     * OUTPUTS: 1
     */
    class Or : public Gate {

    public:
        /// Constructor
        explicit Or(ID id);

        /**
         * Behaves like standard or gate
         **/
        void update() override;
    };
}  // namespace Logicon


#endif //LOGICON_OR_H
