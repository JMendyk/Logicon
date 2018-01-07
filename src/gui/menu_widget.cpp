//
// Created by JMendyk on 18.12.17.
//

#include "gui/menu_widget.h"

// For VerticalSeparator - since re-implementing it
// would required adding many ImGui's internal functions

namespace Logicon {

    ImFont* myFont = nullptr;

    bool MenuWidget::init(GLFWwindow* window) {
        this->window = window;

        static ImFontConfig imFontConfig = ImFontConfig();
        imFontConfig.SizePixels = 32.0f;
        imFontConfig.RasterizerMultiply = 4;
        myFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Medium.ttf", 32.0f, &imFontConfig);

        return true;
    }

    bool MenuWidget::close() {
        return true;
    }

    void MenuWidget::render_ui(const UIVec2 &window_pos, const UIVec2 &window_size) {
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

            ImGui::Button("New", UIVec2(sz, sz));
            ImGui::SameLine();
            ImGui::Button("Open", UIVec2(sz, sz));
            ImGui::SameLine();
            ImGui::Button("Save", UIVec2(sz, sz));
            ImGui::SameLine();

            ImGui::VerticalSeparator();
            ImGui::SameLine();

            ImGui::Button("Play", UIVec2(sz, sz));
            ImGui::SameLine();
            ImGui::Button("Stop", UIVec2(sz, sz));
            ImGui::SameLine();
            ImGui::Button("Reset", UIVec2(sz, sz));
            ImGui::SameLine();

            ImGui::VerticalSeparator();
            ImGui::SameLine();

            static int tickrate = 1000;

            ImGui::PushItemWidth(256);
            ImGui::PushFont(myFont);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, UIVec2(8, 8));
            ImGui::InputInt("", &tickrate, NULL, NULL);
            ImGui::PopStyleVar();
            ImGui::PopFont();
            ImGui::PopItemWidth();

            ImGui::SameLine();
            ImGui::Button("Step-by-step", UIVec2(sz, sz));
            ImGui::SameLine();
        }
        ImGui::End();
    }

} // namespace Logicon
