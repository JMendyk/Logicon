//
// Created by kralizekmd on 09.01.2018
//

#ifndef LOGICON_NAND_H
#define LOGICON_NAND_H


#include "gate.h"

namespace Logicon {
    /**
     * @brief Nand gate implementation.
     * INPUTS:  2
     * OUTPUTS: 1
     */
    class Nand : public Gate {

    public:
        /// Constructor
        explicit Nand(ID id);

        /**
         * Behaves like standard nand gate
         */
        void update() override;
    };
}  // namespace Logicon


#endif //LOGICON_NAND_H
