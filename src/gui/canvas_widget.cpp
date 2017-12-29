//
// Created by JMendyk on 28.12.17.
//

#include "gui/canvas_widget.h"

namespace Logicon {

    bool CanvasWidget::init() {

        this->gCircuit = std::make_shared<GCircuit>();
        if(!this->gCircuit->init())
            return false;

        return true;
    }

    bool CanvasWidget::close() {

        if(!this->gCircuit->close())
            return false;

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

            /*
             * GCircuit
             */
            const UIVec2 g_circuit_pos = UIVec2(0,0);
            const UIVec2 g_circuit_size = UIVec2(ImGui::GetContentRegionAvail());
            this->gCircuit->render_ui(g_circuit_pos, g_circuit_size);
        }
        ImGui::End();
    }

} // namespace Logicon