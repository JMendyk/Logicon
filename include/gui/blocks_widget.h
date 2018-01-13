//
// Created by JMendyk on 18.12.17.
//

#ifndef LOGICON_BLOCKSWIDGET_H
#define LOGICON_BLOCKSWIDGET_H

#include "gui/gUtils.h"

#include <GLFW/glfw3.h>

namespace Logicon {

    class BlocksWidget {
        static BlocksWidget *instance;

//-----------------------------------------------------------------------------
    private:
        BlocksWidget() = default;
    public:
        static BlocksWidget &getInstance();

        BlocksWidget(const BlocksWidget &) = delete;

        void operator=(const BlocksWidget &) = delete;
//-----------------------------------------------------------------------------
    public:
        bool init();

        void render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size);

        bool close();
    };

};

#endif //LOGICON_BLOCKSWIDGET_H
