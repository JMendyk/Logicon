//
// Created by kralizekmd on 09.01.2018
//

#ifndef LOGICON_NOR_H
#define LOGICON_NOR_H


#include "gate.h"

namespace Logicon {
    /**
     * @brief Nor gate implementation.
     * INPUTS:  2
     * OUTPUTS: 1
     */
    class Nor : public Gate {

    public:
        /// Constructor
        explicit Nor(ID id);

        /**
         * Behaves like standard nor gate
         **/
        void update() override;
    };
}  // namespace Logicon


#endif //LOGICON_NOR_H
