//
// Created by JMendyk on 18.12.17.
//

#ifndef LOGICON_MENUWIDGET_H
#define LOGICON_MENUWIDGET_H

#include "gui/gUtils.h"

#include <GLFW/glfw3.h>

namespace Logicon {

    //forward declare App
    class App;

    class MenuWidget {
        static MenuWidget *instance;
        App *app;
        GLFWwindow *window;

        MenuWidget() = default;
    public:
        static MenuWidget *getInstance();
        bool init(App *app, GLFWwindow *window);

        void render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size);

        bool close();
    };

};

#endif //LOGICON_MENUWIDGET_H
