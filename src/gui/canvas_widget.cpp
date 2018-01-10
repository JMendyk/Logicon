//
// Created by JMendyk on 28.12.17.
//

#include <app.h>

namespace Logicon {
    CanvasWidget *CanvasWidget::instance = nullptr;

    bool CanvasWidget::init(App *app) {
        if (instance == nullptr) {
            instance = new CanvasWidget();
        }
        instance->app = app;
        instance->gCircuit = std::make_shared<GCircuit>(app->circuit); // create new gCircuit and init with apps model
        return instance->gCircuit->init();

    }

    bool CanvasWidget::close() {
        return this->gCircuit->close();
    }

    void CanvasWidget::render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size) {
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
            const UI::Vec2 g_circuit_pos = UI::Vec2(0, 0);
            const UI::Vec2 g_circuit_size = UI::Vec2(ImGui::GetContentRegionAvail());
            this->gCircuit->render(g_circuit_pos, g_circuit_size);
        }
        ImGui::End();
    }

    CanvasWidget *CanvasWidget::getInstance() {
        if (instance == nullptr) {
            instance = new CanvasWidget();
        }
        return instance;
    }

    void CanvasWidget::set_current_gate_to_place(GATE_TYPE gate_type) {
        gCircuit->set_current_gate_to_place(gate_type);
    }

} // namespace Logicon