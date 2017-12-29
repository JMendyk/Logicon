//
// Created by JMendyk on 18.12.17.
//

#ifndef LOGICON_MENUWIDGET_H
#define LOGICON_MENUWIDGET_H

#include "widgets/gHelpers.h"

#include <GLFW/glfw3.h>

namespace Logicon {

    class MenuWidget {

        GLFWwindow* window;

    public:
        bool init(GLFWwindow* window);
        void render_ui(const UIVec2 &window_pos, const UIVec2 &window_size);
        bool close();
    };

};

#endif //LOGICON_MENUWIDGET_H
