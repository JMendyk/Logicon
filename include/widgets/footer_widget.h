//
// Created by JMendyk on 18.12.17.
//

#ifndef LOGICON_FOOTERWIDGET_H
#define LOGICON_FOOTERWIDGET_H

#include <widgets/widget_commons.h>

namespace Logicon {

    class FooterWidget {

        GLFWwindow* window;

    public:
        bool init(GLFWwindow* window);
        void render_ui(const ImVec2 &window_pos, const ImVec2 &window_size);
        bool close();
    };

};

#endif //LOGICON_FOOTERWIDGET_H
