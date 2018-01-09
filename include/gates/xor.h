//
// Created by kralizekmd on 09.01.2018
//

#ifndef LOGICON_XOR_H
#define LOGICON_XOR_H


#include "gate.h"

namespace Logicon {
    /**
     * @brief Xor gate implementation.
     * INPUTS:  2
     * OUTPUTS: 1
     */
    class Xor : public Gate {

    public:
        /// Constructor
        explicit Xor(ID id);

        /**
         * Behaves like standard xor gate
         **/
        void update() override;
    };
}  // namespace Logicon

#endif //LOGICON_XOR_H
