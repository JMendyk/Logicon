//
// Created by JMendyk on 18.12.17.
//

#include "widgets/footer_widget.h"

namespace Logicon {

    bool FooterWidget::init(GLFWwindow* window) {
        this->window = window;
        return true;
    }

    bool FooterWidget::close() {
        return true;
    }

    void FooterWidget::render_ui(const ImVec2 &window_pos, const ImVec2 &window_size) {

    }

};
