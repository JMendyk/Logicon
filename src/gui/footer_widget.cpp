//
// Created by JMendyk on 18.12.17.
//

#include "gui/footer_widget.h"

// For VerticalSeparator - since re-implementing it
// would required adding many ImGui's internal functions

namespace Logicon {

    FooterWidget &FooterWidget::getInstance() {
        static FooterWidget instance;
        return instance;
    }
//-----------------------------------------------------------------------------

    bool FooterWidget::init() {
        return true;
    }

    bool FooterWidget::close() {
        return true;
    }

    void FooterWidget::render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size) {
        ImGuiWindowFlags window_flags = 0
                                        | ImGuiWindowFlags_NoTitleBar
                                        | ImGuiWindowFlags_NoResize
                                        | ImGuiWindowFlags_NoMove;

        ImGui::Begin("Footer Widget", nullptr, window_flags);
        {
            ImGui::SetWindowPos(window_pos, ImGuiCond_Always);
            ImGui::SetWindowSize(window_size, ImGuiCond_Always);

            const int left_area_fields = 3;

            // Left area
            for (int idx = 0; idx < left_area_fields; idx++) {
                if (idx == 0) {
                    ImGui::Text("Logicon");
                } else if (idx == 1) {
                    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
                } else if (idx == 2) {
                    showHelpMarker(
                        "Top menu:\n"
                        "\tNew circuit\n"
                        "\tLoad circuit from file\n"
                        "\tSave circuit to file\n"
                        "\tStart/pause/reset logic simulation\n"
                        "\tChange simulation speed, switch to step-by-step mode\n"
                        "\tLoad/save states of free (not connected) inputs/outputs\n"
                        "Right menu:\n"
                        "\tAdd gates by selecting one of them. In main area click where gates should be placed. "
                        "To finish adding gate click the same one again or press Esc.\n"
                        "Main area (circuit):\n"
                        "\tMove gates around by dragging and dropping.\n"
                        "\tConnect gates by dragging and dropping between desired ports.\n"
                        "\tRMB to remove connection(s) coming out of hovered port.\n"
                        "\tSome gates respond to clicking - such as input or switch.\n"
                        "\tRMB on gate to open context menu.\n"
                        "\tDEL+CLICK to disconnect port with everything or remove block.\n"
                        "\tLMB to switch active elements.\n"
                        "\tHold MMB and drag to scroll canvas.\n"
                    );
                }
                if(idx < left_area_fields - 1) {
                    ImGui::SameLine();
                    ImGui::VerticalSeparator();
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

            // The 100.0f is just a guess size for the first frame.
            static const float ItemSpacing = ImGui::GetStyle().ItemSpacing.x;
            float pos = 0;


            for (int i = static_cast<int>(statues.size() - 1); i >= 0; --i) {
                pos += status_widths[i] + ItemSpacing;
                ImGui::SameLine((ImGui::GetWindowWidth() - pos));
                ImGui::BeginGroup();
                ImGui::Text(statues[i].c_str());
                ImGui::SameLine();
                if(i < statues.size() - 1) ImGui::VerticalSeparator();
                ImGui::EndGroup();
                status_widths[i] = ImGui::GetItemRectSize().x;
            }

            statues.clear();

        }
        ImGui::End();
    }

    void FooterWidget::showHelpMarker(const char* desc) {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(450.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    void FooterWidget::pushStatus(std::string str) {
        statues.push_back(str);
        if(statues.size() > status_widths.size())
            status_widths.resize(statues.size(), 100.0f);
    }

} // namespace Logicon
