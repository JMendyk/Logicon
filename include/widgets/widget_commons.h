//
// Created by JMendyk on 21.12.17.
//

#ifndef LOGICON_WIDGET_COMMONS_H
#define LOGICON_WIDGET_COMMONS_H

#include <GLFW/glfw3.h>

#include <imgui.h>

namespace Logicon {

    static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x+rhs.x, lhs.y+rhs.y); }
    static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x-rhs.x, lhs.y-rhs.y); }

    namespace UI {
        const int MARGIN = 16;
        const int MENU_WIDGET_HEIGHT = 64;
        const int FOOTER_WIDGET_HEIGHT = 32;
        const int BLOCKS_WIDGET_WIDTH = 300;
    }

}  // namespace Logicon


#endif //LOGICON_WIDGET_COMMONS_H
