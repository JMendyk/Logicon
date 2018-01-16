//
// Created by kralizekmd on 09.01.2018
//

#ifndef LOGICON_XNOR_H
#define LOGICON_XNOR_H


#include "gate.h"

namespace Logicon {
    /**
     * @brief Xnor gate implementation.
     * INPUTS:  2
     * OUTPUTS: 1
     */
    class Xnor : public Gate {

    public:
        /// Constructor
        explicit Xnor(ID id);

        /**
         * Behaves like standard xnor gate
         **/
        void update() override;
    };
}  // namespace Logicon

#endif //LOGICON_XNOR_H
