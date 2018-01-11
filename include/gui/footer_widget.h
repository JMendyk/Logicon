//
// Created by JMendyk on 18.12.17.
//

#ifndef LOGICON_FOOTERWIDGET_H
#define LOGICON_FOOTERWIDGET_H

#include "gui/gUtils.h"

#include <GLFW/glfw3.h>

namespace Logicon {

    // forward declare App
    class App;

    class FooterWidget {
        static FooterWidget *instance;
        App *app;
        GLFWwindow *window;
        std::string str1;
        std::string str2;
        std::string str3;
        FooterWidget() = default;
    public:
        static FooterWidget *getInstance();

        bool init(App *app, GLFWwindow *window);

        void render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size);

        bool close();

        void setStr(int idx, std::string str);
    };

};

#endif //LOGICON_FOOTERWIDGET_H
