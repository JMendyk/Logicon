//
// Created by JMendyk on 18.12.17.
//

#ifndef LOGICON_BLOCKSWIDGET_H
#define LOGICON_BLOCKSWIDGET_H

#include "gui/gUtils.h"

namespace Logicon {

    class BlocksWidget {

//-----------------------------------------------------------------------------
    private:
        BlocksWidget() = default;

    public:
        static BlocksWidget &getInstance();

        BlocksWidget(const BlocksWidget &) = delete;

        void operator=(const BlocksWidget &) = delete;
//-----------------------------------------------------------------------------
    public:
        GATE_TYPE current_gate_to_place;
        bool PLACEMENT_MODE;

        bool init();

        void render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size);

        bool close();
    };

};

#endif //LOGICON_BLOCKSWIDGET_H
