//
// Created by JMendyk on 18.12.17.
//

#include "gui/blocks_widget.h"

// For EndColumn - without it ImGui::Columns looks strange
// However, nesting column layouts is not advised per ImGui documentation
#include <imgui_internal.h>

namespace Logicon {

    bool BlocksWidget::init(GLFWwindow* window) {
        this->window = window;
        return true;
    }

    bool BlocksWidget::close() {
        return true;
    }

    void BlocksWidget::render_ui(const UIVec2 &window_pos, const UIVec2 &window_size) {
        ImGuiWindowFlags window_flags = 0
            | ImGuiWindowFlags_NoTitleBar
            | ImGuiWindowFlags_NoResize
            | ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_AlwaysVerticalScrollbar;

        ImGui::Begin("Blocks Widget", nullptr, window_flags);
        {
            ImGui::SetWindowPos(window_pos, ImGuiCond_Always);
            ImGui::SetWindowSize(window_size, ImGuiCond_Always);

            ImGui::BeginGroup();
            ImGui::Columns(2, nullptr, true);

            /*
             * NOTE: I (@JMendyk) encountered some issues with GetContentRegionAvailWidth that kept changing values
             * every frame. I then decided to statically save this value and use saved one every frame.
             * However, later on this issue disappeared. Let's see how it will unfold.
             *
             * NOTE (2018.01.07 22:17): Here we go again...
             * Let's just always display vertical scrollbar and avoid sophisticated hacks.
             */

            float size = ImGui::GetContentRegionAvailWidth();

            for(int i = 0; i < 12; i++) {
                ImGui::PushID(i);
                ImGui::Button("1,1", UIVec2(size, size));
                ImGui::Spacing();
                ImGui::NextColumn();
                ImGui::PopID();
            }

            ImGui::EndColumns();
            ImGui::EndGroup();

        }
        ImGui::End();
    }

} // namespace Logicon
