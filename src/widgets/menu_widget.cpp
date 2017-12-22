//
// Created by JMendyk on 18.12.17.
//

#include "widgets/menu_widget.h"

// For VerticalSeparator - since re-implementing it
// would required adding many ImGui's internal functions
#include <imgui_internal.h>

namespace Logicon {

    ImFont* myFont = nullptr;

    bool MenuWidget::init(GLFWwindow* window) {
        this->window = window;

        static ImFontConfig imFontConfig = ImFontConfig();
        imFontConfig.SizePixels = 32.0f;
        imFontConfig.RasterizerMultiply = 4;
        myFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("../dependencies/imgui/extra_fonts/Roboto-Medium.ttf", 32.0f, &imFontConfig);

        return true;
    }

    bool MenuWidget::close() {
        return true;
    }

    void MenuWidget::render_ui(const ImVec2 &window_pos, const ImVec2 &window_size) {
        ImGuiWindowFlags window_flags =
                0
                | ImGuiWindowFlags_NoTitleBar
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoMove;

        ImGui::Begin("Menu Widget", nullptr, window_flags);
        {
            ImGui::SetWindowPos(window_pos, ImGuiCond_Always);
            ImGui::SetWindowSize(window_size, ImGuiCond_Always);

            const int sz = static_cast<int>(window_size.y - 16);

            ImGui::Button("New", ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::Button("Open", ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::Button("Save", ImVec2(sz, sz));
            ImGui::SameLine();

            ImGui::VerticalSeparator();
            ImGui::SameLine();

            ImGui::Button("Play", ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::Button("Stop", ImVec2(sz, sz));
            ImGui::SameLine();
            ImGui::Button("Reset", ImVec2(sz, sz));
            ImGui::SameLine();

            ImGui::VerticalSeparator();
            ImGui::SameLine();

            static int tickrate = 1000;

            ImGui::PushItemWidth(256);
            ImGui::PushFont(myFont);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 8));
            ImGui::InputInt("", &tickrate, NULL, NULL);
            ImGui::PopStyleVar();
            ImGui::PopFont();
            ImGui::PopItemWidth();

            ImGui::SameLine();
            ImGui::Button("Step-by-step", ImVec2(sz, sz));
            ImGui::SameLine();
        }
        ImGui::End();
    }

} // namespace Logicon
