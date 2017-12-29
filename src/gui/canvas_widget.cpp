//
// Created by JMendyk on 28.12.17.
//

#include "gui/canvas_widget.h"

namespace Logicon {

    bool CanvasWidget::init() {

        return true;
    }

    bool CanvasWidget::close() {

        return true;
    }

    void CanvasWidget::render_ui(const UIVec2 &window_pos, const UIVec2 &window_size) {
        ImGuiWindowFlags window_flags = 0
            | ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoMove;

        ImGui::Begin("Canvas Widget", nullptr, window_flags);
        {
            ImGui::SetWindowPos(window_pos, ImGuiCond_Always);
            ImGui::SetWindowSize(window_size, ImGuiCond_Always);
        }
        ImGui::End();
    }

} // namespace Logicon