//
// Created by JMendyk on 29.12.17.
//

#ifndef LOGICON_G_BLOCK_H
#define LOGICON_G_BLOCK_H

#include "types.h"
#include "gui/gHelpers.h"

#include "iGCircuit.h"

#include "graphics.h"

namespace Logicon {

    class GBlock {

        // Initialized by constructor //
        UIVec2 size;
        Texture texture;
        Data data; // label etc. (for future)
        // GInput gInputs[];   // handle detection of changing Connections
        // GOutput gOutputs[]; // maybe replaced by (G?)Port

        // Initialized when placed in GCircuit //
        std::shared_ptr<IGCircuit> parent; // access to i_move, i_isOccupied
        ID id;
        UIVec2 pos;

        bool is_dragged;
        UIVec2 drag_pos;

      public:

        GBlock(const UIVec2 &size, const Texture &texture, const Data &data);
        explicit GBlock(GBlock *other);

        void place(std::shared_ptr<IGCircuit> parent, ID id, UIVec2 pos);

        void render();
        /* private */ void update();

        Port getPortAt(UIVec2 port_pos); // absolute position <=> get port at top-left corner of block with port_pos == this->pos

        ID getId() const;

        UIRect getRect() const;
    };

} // namespace Logicon

#endif //LOGICON_G_BLOCK_H
