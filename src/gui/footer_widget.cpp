//
// Created by JMendyk on 18.12.17.
//

#include "gui/footer_widget.h"

#include <iostream>

// For VerticalSeparator - since re-implementing it
// would required adding many ImGui's internal functions

namespace Logicon {

    FooterWidget *FooterWidget::instance = nullptr;

    bool FooterWidget::init(App *app, GLFWwindow *window) {
        if (instance == nullptr) {
            instance = new FooterWidget();
        }
        instance->app = app;
        instance->window = window;
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

            static const int elements_count = 3;
            // The 100.0f is just a guess size for the first frame.
            static std::vector<float> widths(elements_count, {100.0f});
            static const float ItemSpacing = ImGui::GetStyle().ItemSpacing.x;
            float pos = 0;

            for (int idx = elements_count - 1; idx >= 0; idx--) {
                pos += widths[idx] + ItemSpacing;
                ImGui::SameLine(ImGui::GetWindowWidth() - pos);
                ImGui::BeginGroup();
                if (idx == 0) {
                    ImGui::Text(str1.c_str());
                    ImGui::SameLine();
                    ImGui::VerticalSeparator();
                } else if (idx == 1) {
                    ImGui::Text(str2.c_str());
                    ImGui::SameLine();
                    ImGui::VerticalSeparator();
                } else if (idx == 2) {
                    ImGui::Text(str3.c_str());
                }
                ImGui::EndGroup();
                widths[idx] = ImGui::GetItemRectSize().x;
            }

        }
        ImGui::End();
    }

    FooterWidget *FooterWidget::getInstance() {
        if (instance == nullptr) {
            instance = new FooterWidget();
        }
        return instance;
    }

    void FooterWidget::setStr(int idx, std::string str) {
        switch (idx) {
            case 1:
                str1 = "x:" + str;
                break;
            case 2:
                str2 = "y:" + str;
                break;
            case 3:
                str3 = str;
                break;
            default:
                break;
        }
    }

} // namespace Logicon
