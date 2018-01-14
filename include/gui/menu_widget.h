//
// Created by JMendyk on 18.12.17.
//

#ifndef LOGICON_MENUWIDGET_H
#define LOGICON_MENUWIDGET_H

#include "gui/gUtils.h"

#include <GLFW/glfw3.h>

namespace Logicon {


    class MenuWidget {

        ImFont *myFont;
//-----------------------------------------------------------------------------
    private:
        MenuWidget() = default;

    public:
        static MenuWidget &getInstance();

        MenuWidget(const MenuWidget &) = delete;

        void operator=(const MenuWidget &) = delete;
//-----------------------------------------------------------------------------
    public:
        bool init();

        void render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size, const UI::Vec2 &dialog_pos, const UI::Vec2 &dialog_size);

        bool close();
    };

};

#endif //LOGICON_MENUWIDGET_H
