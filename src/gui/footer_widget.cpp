//
// Created by JMendyk on 18.12.17.
//

#include "gui/footer_widget.h"

#include <iostream>

// For VerticalSeparator - since re-implementing it
// would required adding many ImGui's internal functions

namespace Logicon {

    bool FooterWidget::init(App *app, GLFWwindow *window) {
        this->app = app;
        this->window = window;
        return true;
    }

    bool FooterWidget::close() {
        return true;
    }

    // TODO: Update footer dummy text
    void FooterWidget::render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size) {
        ImGuiWindowFlags window_flags = 0
                                        | ImGuiWindowFlags_NoTitleBar
                                        | ImGuiWindowFlags_NoResize
                                        | ImGuiWindowFlags_NoMove;

        ImGui::Begin("Footer Widget", nullptr, window_flags);
        {
            ImGui::SetWindowPos(window_pos, ImGuiCond_Always);
            ImGui::SetWindowSize(window_size, ImGuiCond_Always);

            // Left area
            for (int idx = 0; idx < 2; idx++) {
                if (idx == 0) {
                    ImGui::Text("Logicon");
                    ImGui::SameLine();
                    ImGui::VerticalSeparator();
                } else if (idx == 1) {
                    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
                }
                ImGui::SameLine();
            }

            // Right area

            /*
             * Solution based on an answer to ImGui issue #934
             * https://github.com/ocornut/imgui/issues/934#issuecomment-340231002
             * I (@JMendyk) refactored mentioned solution using a for-loop
             * thus order of elements is the same as they will appear on the screen
             */

            static const int elements_count = 4;
            // The 100.0f is just a guess size for the first frame.
            static std::vector<float> widths(elements_count, {100.0f});
            static const float ItemSpacing = ImGui::GetStyle().ItemSpacing.x;
            float pos = 0;

            for (int idx = elements_count - 1; idx >= 0; idx--) {
                pos += widths[idx] + ItemSpacing;
                ImGui::SameLine(ImGui::GetWindowWidth() - pos);
                ImGui::BeginGroup();
                if (idx == 0) {
                    ImGui::Text("In: %d", 1);
                    ImGui::SameLine();
                    ImGui::VerticalSeparator();
                } else if (idx == 1) {
                    ImGui::Text("Out: %d", 0);
                    ImGui::SameLine();
                    ImGui::VerticalSeparator();
                } else if (idx == 2) {
                    ImGui::Text("Gates: %d", 3);
                    ImGui::SameLine();
                    ImGui::VerticalSeparator();
                } else if (idx == 3) {
                    ImGui::Text("File: %s", "Circuit1");
                }
                ImGui::EndGroup();
                widths[idx] = ImGui::GetItemRectSize().x;
            }

        }
        ImGui::End();
    }

} // namespace Logicon
