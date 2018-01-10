//
// Created by JMendyk on 18.12.17.
//

#ifndef LOGICON_BLOCKSWIDGET_H
#define LOGICON_BLOCKSWIDGET_H

#include "gui/gUtils.h"

#include <GLFW/glfw3.h>

namespace Logicon {

    // forward declare App
    class App;

    class BlocksWidget {
        static BlocksWidget *instance;

        App *app;
        GLFWwindow* window;

        BlocksWidget() = default;
    public:
        static BlocksWidget *getInstance();
        bool init(App *app, GLFWwindow *window);

        void render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size);
        bool close();
    };

};

#endif //LOGICON_BLOCKSWIDGET_H
