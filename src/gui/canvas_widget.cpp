//
// Created by JMendyk on 28.12.17.
//

#include <app.h>

namespace Logicon {

    CanvasWidget &CanvasWidget::getInstance() {
        static CanvasWidget instance;
        return instance;
    }
//-----------------------------------------------------------------------------

    bool CanvasWidget::init(std::shared_ptr<Circuit> circuit) {
        gCircuit = std::make_shared<GCircuit>(circuit);
        return true;
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

    void CanvasWidget::setGCircuit(const std::shared_ptr<GCircuit> gCircuit) {
        this->gCircuit = gCircuit; // create new gCircuit and init with apps model
    }

    const std::shared_ptr<GCircuit> &CanvasWidget::getGCircuit() const {
        return gCircuit;
    }

} // namespace Logicon