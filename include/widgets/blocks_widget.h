//
// Created by JMendyk on 18.12.17.
//

#ifndef LOGICON_BLOCKSWIDGET_H
#define LOGICON_BLOCKSWIDGET_H

#include <widgets/widget_commons.h>

namespace Logicon {

    class BlocksWidget {

        GLFWwindow* window;

    public:
        bool init(GLFWwindow* window);
        void render_ui(const ImVec2 &window_pos, const ImVec2 &window_size);
        bool close();
    };

};

#endif //LOGICON_BLOCKSWIDGET_H
