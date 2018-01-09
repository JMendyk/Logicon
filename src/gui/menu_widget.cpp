//
// Created by JMendyk on 18.12.17.
//

#include <assetLoader.h>
#include <app.h>

// For VerticalSeparator - since re-implementing it
// would required adding many ImGui's internal functions

namespace Logicon {

    ImFont *myFont = nullptr;

    bool MenuWidget::init(App *app, GLFWwindow *window) {
        this->app = app;
        this->window = window;

        static ImFontConfig imFontConfig = ImFontConfig();
        imFontConfig.SizePixels = 32.0f;
        imFontConfig.RasterizerMultiply = 4;
        myFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Medium.ttf", 32.0f, &imFontConfig);

        return myFont != NULL;
    }

    bool MenuWidget::close() {
        return true;
    }

    void MenuWidget::render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size) {
        ImGuiWindowFlags window_flags =
                0
                | ImGuiWindowFlags_NoTitleBar
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoMove;

        ImGui::Begin("Menu Widget", nullptr, window_flags);
        {
            ImGui::SetWindowPos(window_pos, ImGuiCond_Always);
            ImGui::SetWindowSize(window_size, ImGuiCond_Always);

            //ImGui::Button("New", UI::Vec2(sz, sz));
            ImGui::ImageButton(reinterpret_cast<ImTextureID>(Logicon::AssetLoader::icon_new().textureId),
                               {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                               UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                               ImVec4(0, 0, 0, 0),
                               UI::MENU_WIDGET_BUTTON_FG_COLOR
            );
            ImGui::SameLine();
            ImGui::ImageButton(reinterpret_cast<ImTextureID>(Logicon::AssetLoader::icon_open().textureId),
                               {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                               UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                               ImVec4(0, 0, 0, 0),
                               UI::MENU_WIDGET_BUTTON_FG_COLOR
            );
            ImGui::SameLine();
            ImGui::ImageButton(reinterpret_cast<ImTextureID>(Logicon::AssetLoader::icon_save().textureId),
                               {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                               UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                               ImVec4(0, 0, 0, 0),
                               UI::MENU_WIDGET_BUTTON_FG_COLOR
            );
            ImGui::SameLine();

            ImGui::VerticalSeparator();
            ImGui::SameLine();

            ImGui::ImageButton(reinterpret_cast<ImTextureID>(Logicon::AssetLoader::icon_play().textureId),
                               {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                               UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                               ImVec4(0, 0, 0, 0),
                               UI::MENU_WIDGET_BUTTON_FG_COLOR
            );
            ImGui::SameLine();
            ImGui::ImageButton(reinterpret_cast<ImTextureID>(Logicon::AssetLoader::icon_pause().textureId),
                               {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                               UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                               ImVec4(0, 0, 0, 0),
                               UI::MENU_WIDGET_BUTTON_FG_COLOR
            );
            ImGui::SameLine();
            ImGui::ImageButton(reinterpret_cast<ImTextureID>(Logicon::AssetLoader::icon_restart().textureId),
                               {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                               UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                               ImVec4(0, 0, 0, 0),
                               UI::MENU_WIDGET_BUTTON_FG_COLOR
            );
            ImGui::SameLine();

            ImGui::VerticalSeparator();
            ImGui::SameLine();

            ImGui::PushItemWidth(256);
            ImGui::PushFont(myFont);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, UI::Vec2(8, 8));
            ImGui::InputInt("", &(app->tickrate), 0, 0);
            ImGui::PopStyleVar();
            ImGui::PopFont();
            ImGui::PopItemWidth();

            ImGui::SameLine();
            ImGui::ImageButton(reinterpret_cast<ImTextureID>(Logicon::AssetLoader::icon_step().textureId),
                               {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                               UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                               ImVec4(0, 0, 0, 0),
                               UI::MENU_WIDGET_BUTTON_FG_COLOR
            );
            ImGui::SameLine();
        }
        ImGui::End();
    }

} // namespace Logicon
