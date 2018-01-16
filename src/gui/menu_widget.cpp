//
// Created by JMendyk on 18.12.17.
//

#include <assetLoader.h>
#include <app.h>

// For VerticalSeparator - since re-implementing it
// would required adding many ImGui's internal functions

namespace Logicon {

    MenuWidget &MenuWidget::getInstance() {
        static MenuWidget instance;
        return instance;
    }
//-----------------------------------------------------------------------------

    bool MenuWidget::init() {

        static ImFontConfig imFontConfig = ImFontConfig();
        imFontConfig.SizePixels = 32.0f;
        imFontConfig.RasterizerMultiply = 4;
        myFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Medium.ttf", 32.0f, &imFontConfig);

        return myFont != nullptr;
    }

    bool MenuWidget::close() {
        return true;
    }

    void MenuWidget::render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size, const UI::Vec2 &dialog_pos,
                            const UI::Vec2 &dialog_size) {
        ImGuiWindowFlags window_flags =
                0
                | ImGuiWindowFlags_NoTitleBar
                | ImGuiWindowFlags_NoResize
                | ImGuiWindowFlags_NoMove;

        ImGui::Begin("Menu Widget", nullptr, window_flags);
        {
            ImGui::SetWindowPos(window_pos, ImGuiCond_Always);
            ImGui::SetWindowSize(window_size, ImGuiCond_Always);

            /// NEW
            if (ImGui::ImageButton(
                    reinterpret_cast<ImTextureID>(Logicon::AssetLoader::getIconTexture(AssetLoader::NEW).textureId),
                    {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                    UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                    ImVec4(0, 0, 0, 0), UI::MENU_WIDGET_BUTTON_NORMAL_COLOR
            )) {
                CanvasWidget::getInstance().getGCircuit()->clear();
            }
            ImGui::SameLine();
            /// OPEN
            static ImGuiFs::Dialog open_dlg;
            const bool open_clicked = ImGui::ImageButton(
                    reinterpret_cast<ImTextureID>(Logicon::AssetLoader::getIconTexture(AssetLoader::OPEN).textureId),
                    {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                    UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                    ImVec4(0, 0, 0, 0), UI::MENU_WIDGET_BUTTON_NORMAL_COLOR
            );

            const char *open_path = open_dlg.chooseFileDialog(
                    open_clicked,
                    nullptr,
                    Data::LOGICON_FILE_EXTENSION.c_str(),
                    nullptr,
                    dialog_size,
                    dialog_pos
            );
            if (strlen(open_path) > 0) {
                auto gc = Data::read(open_path);
                CanvasWidget::getInstance().setGCircuit(gc);
                App::getInstance().circuit = gc->getCircuit();
            }
            ImGui::SameLine();
            /// SAVE
            static ImGuiFs::Dialog save_dlg;
            const bool save_clicked = ImGui::ImageButton(
                    reinterpret_cast<ImTextureID>(Logicon::AssetLoader::getIconTexture(AssetLoader::SAVE).textureId),
                    {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                    UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                    ImVec4(0, 0, 0, 0), UI::MENU_WIDGET_BUTTON_NORMAL_COLOR
            );

            const char *save_path = save_dlg.saveFileDialog(
                    save_clicked,
                    nullptr,
                    ("circuit" + Data::LOGICON_FILE_EXTENSION).c_str(),
                    Data::LOGICON_FILE_EXTENSION.c_str(),
                    nullptr,
                    dialog_size,
                    dialog_pos
            );
            if (strlen(save_path) > 0) {
                Data::save(save_path, CanvasWidget::getInstance().getGCircuit());
            }
            ImGui::SameLine();

            ImGui::VerticalSeparator();
            ImGui::SameLine();

            /// PLAY
            if (ImGui::ImageButton(
                    reinterpret_cast<ImTextureID>(Logicon::AssetLoader::getIconTexture(AssetLoader::PLAY).textureId),
                    {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                    UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                    ImVec4(0, 0, 0, 0), App::getInstance().state == App::STATE::RUNNING ?
                                        UI::MENU_WIDGET_BUTTON_PLAY_PUSHED_COLOR : UI::MENU_WIDGET_BUTTON_NORMAL_COLOR
            )) {
                App::getInstance().state = App::STATE::RUNNING;
            }
            ImGui::SameLine();
            /// PAUSE
            if (ImGui::ImageButton(
                    reinterpret_cast<ImTextureID>(Logicon::AssetLoader::getIconTexture(AssetLoader::PAUSE).textureId),
                    {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                    UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                    ImVec4(0, 0, 0, 0), App::getInstance().state == App::STATE::PAUSED ?
                                        UI::MENU_WIDGET_BUTTON_PAUSE_PUSHED_COLOR : UI::MENU_WIDGET_BUTTON_NORMAL_COLOR
            )) {
                App::getInstance().state = App::STATE::PAUSED;
            }
            ImGui::SameLine();
            /// RESTART
            if (ImGui::ImageButton(
                    reinterpret_cast<ImTextureID>(Logicon::AssetLoader::getIconTexture(AssetLoader::RESTART).textureId),
                    {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                    UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                    ImVec4(0, 0, 0, 0), UI::MENU_WIDGET_BUTTON_NORMAL_COLOR
            )) {
                App::getInstance().state = App::STATE::RESTART;
            }
            ImGui::SameLine();

            /// TICKRATE
            ImGui::VerticalSeparator();
            ImGui::SameLine();

            ImGui::PushItemWidth(256);
            ImGui::PushFont(myFont);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, UI::Vec2(8, 8));
            ImGui::InputInt("", &(App::getInstance().tickrate), 0, 0);
            ImGui::PopStyleVar();
            ImGui::PopFont();
            ImGui::PopItemWidth();

            ImGui::SameLine();
            /// STEP
            if (ImGui::ImageButton(
                    reinterpret_cast<ImTextureID>(Logicon::AssetLoader::getIconTexture(AssetLoader::STEP).textureId),
                    {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                    UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                    ImVec4(0, 0, 0, 0),
                    UI::MENU_WIDGET_BUTTON_NORMAL_COLOR
            )) {
                App::getInstance().state = App::PAUSED;
                App::getInstance().STEP_NEXT_STEP = true;
            }
            ImGui::SameLine();

            /// LOAD INPUTS
            ImGui::VerticalSeparator();
            ImGui::SameLine();
            static ImGuiFs::Dialog load_free_inputs_dlg;
            const bool load_free_inputs_clicked = ImGui::ImageButton(
                    reinterpret_cast<ImTextureID>(Logicon::AssetLoader::getIconTexture(
                            AssetLoader::LOAD_INPUTS).textureId),
                    {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                    UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                    ImVec4(0, 0, 0, 0), UI::MENU_WIDGET_BUTTON_NORMAL_COLOR
            );

            const char *load_free_inputs_path = load_free_inputs_dlg.chooseFileDialog(
                    load_free_inputs_clicked,
                    nullptr,
                    Data::FREE_IO_FILE_EXTENSION.c_str(),
                    nullptr,
                    dialog_size,
                    dialog_pos
            );
            if (strlen(load_free_inputs_path) > 0) {
                Data::loadFreeInputs(load_free_inputs_path, CanvasWidget::getInstance().getGCircuit());
            }

            /// SAVE OUTPUTS
            ImGui::SameLine();
            static ImGuiFs::Dialog save_free_outputs_dlg;
            const bool save_free_outputs_clicked = ImGui::ImageButton(
                    reinterpret_cast<ImTextureID>(Logicon::AssetLoader::getIconTexture(
                            AssetLoader::SAVE_OUTPUTS).textureId),
                    {Logicon::UI::MENU_WIDGET_BUTTON_SIZE, Logicon::UI::MENU_WIDGET_BUTTON_SIZE},
                    UI::Vec2(0, 0), UI::Vec2(1, 1), 0,
                    ImVec4(0, 0, 0, 0), UI::MENU_WIDGET_BUTTON_NORMAL_COLOR
            );

            const char *save_free_outputs_path = save_free_outputs_dlg.saveFileDialog(
                    save_free_outputs_clicked,
                    nullptr,
                    ("outputs" + Data::FREE_IO_FILE_EXTENSION).c_str(),
                    Data::FREE_IO_FILE_EXTENSION.c_str(),
                    nullptr,
                    dialog_size,
                    dialog_pos
            );
            if (strlen(save_free_outputs_path) > 0) {
                Data::saveFreeOutputs(save_free_outputs_path, CanvasWidget::getInstance().getGCircuit());
            }
        }
        ImGui::End();
    }

} // namespace Logicon
