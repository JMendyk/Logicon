//
// Created by JMendyk on 18.12.17.
//

#ifndef LOGICON_BLOCKSWIDGET_H
#define LOGICON_BLOCKSWIDGET_H

#include "widgets/gHelpers.h"

#include <GLFW/glfw3.h>

namespace Logicon {

    class BlocksWidget {

        GLFWwindow* window;

    public:
        bool init(GLFWwindow* window);
        void render_ui(const UIVec2 &window_pos, const UIVec2 &window_size);
        bool close();
    };

};

#endif //LOGICON_BLOCKSWIDGET_H
