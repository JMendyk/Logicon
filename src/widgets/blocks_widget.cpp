//
// Created by JMendyk on 18.12.17.
//

#include "widgets/blocks_widget.h"

namespace Logicon {

    bool BlocksWidget::init(GLFWwindow* window) {
        this->window = window;
        return true;
    }

    bool BlocksWidget::close() {
        return true;
    }

    void BlocksWidget::render_ui(const ImVec2 &window_pos, const ImVec2 &window_size) {

    }

};
