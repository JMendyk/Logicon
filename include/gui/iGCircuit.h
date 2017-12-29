//
// Created by JMendyk on 28.12.17.
//

#ifndef LOGICON_G_CIRCUIT_INTERFACE_H
#define LOGICON_G_CIRCUIT_INTERFACE_H

#include "types.h"

#include "gui/gHelpers.h"

namespace Logicon {

    class IGCircuit : public std::enable_shared_from_this<IGCircuit> {

      public:
        /**
         * @brief To be called by GBlock in order to request moving to new position
         * @param ID of GBlock
         * @param pos position
         * @return true if move operation was successful
         */
        virtual bool i_move(ID id, UIVec2 pos) = 0;

        /**
         * @breif To be called by GBlock in order to check if in the rectangle all cells are either free or belong to GBlock
         * @param id ID of GBlock
         * @param rect Rectangle to check
         * @return false if all cells are either free or belong to GBlock
         */
        virtual bool i_isOccupied(ID id, UIRect rect) = 0;

        // TODO: Implement
        // virtual void i_gateClickAction() = 0;
    };

} // namespace Logicon

#endif //LOGICON_G_CIRCUIT_INTERFACE_H
