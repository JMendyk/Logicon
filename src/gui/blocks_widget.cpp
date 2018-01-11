//
// Created by JMendyk on 18.12.17.
//

#include <graphics.h>
#include <assetLoader.h>
#include "gui/blocks_widget.h"

#include "app.h"

// For EndColumn - without it ImGui::Columns looks strange
// However, nesting column layouts is not advised per ImGui documentation

namespace Logicon {
    BlocksWidget *BlocksWidget::instance = nullptr;

    bool BlocksWidget::init(App *app, GLFWwindow *window) {
        if (instance == nullptr) {
            instance = new BlocksWidget();
        }
        instance->app = app;
        instance->window = window;
        return true;
    }

    bool BlocksWidget::close() {
        return true;
    }

    void BlocksWidget::render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size) {
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

            static GATE_TYPE current_gate_to_place = NO_GATE;
            static auto set_current_gate_to_place = [this](GATE_TYPE gate_type) {
                if(gate_type == current_gate_to_place) {
                    current_gate_to_place = NO_GATE;
                } else {
                    current_gate_to_place = gate_type;
                }

                app->canvasWidget->getGCircuit()->set_current_gate_to_place(current_gate_to_place);
            };

            static auto gate_preview = [set_current_gate_to_place](ImGuiID id, GATE_TYPE gate_type, Texture tex, float size) {
                ImGui::PushID(id);
                float height = size / (5.0f/3);

                if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(tex.textureId),
                                       UI::Vec2(height * ((float)tex.width)/tex.height, height),
                                       UI::Vec2(0, 0),
                                       UI::Vec2(1, 1),
                                       0, ImColor(0, 0, 0, 0), current_gate_to_place == gate_type ? ImColor(128, 128, 128, 200): ImColor(255, 255, 255, 200))) {
                    set_current_gate_to_place(gate_type);
                }
                ImGui::Spacing();
                ImGui::NextColumn();
                ImGui::PopID();
            };

            // TODO: Uncomment gates when their implementations will be available

            gate_preview(ImGui::GetID("gate_or"), GATE_TYPE::OR, AssetLoader::gate_or(), size);
            gate_preview(ImGui::GetID("gate_and"), GATE_TYPE::AND, AssetLoader::gate_and(), size);

            gate_preview(ImGui::GetID("gate_nor"), GATE_TYPE::NOR, AssetLoader::gate_nor(), size);
            gate_preview(ImGui::GetID("gate_nand"), GATE_TYPE::NAND, AssetLoader::gate_nand(), size);

            gate_preview(ImGui::GetID("gate_not"), GATE_TYPE::NOT, AssetLoader::gate_not(), size);
            gate_preview(ImGui::GetID("gate_xnor"), GATE_TYPE::XNOR, AssetLoader::gate_xnor(), size);

            gate_preview(ImGui::GetID("gate_xor"), GATE_TYPE::XOR, AssetLoader::gate_xor(), size);

            gate_preview(ImGui::GetID("gate_switch_off"), GATE_TYPE::SWITCH, AssetLoader::gate_switch_off(), size);
            gate_preview(ImGui::GetID("gate_delay"), GATE_TYPE::DELAY, AssetLoader::gate_delay(), size);

            gate_preview(ImGui::GetID("gate_input_low"), GATE_TYPE::INPUT, AssetLoader::gate_input_low(), size);
            gate_preview(ImGui::GetID("gate_clock"), GATE_TYPE::CLOCK, AssetLoader::gate_clock(), size);

            ImGui::EndColumns();
            ImGui::EndGroup();

        }
        ImGui::End();
    }

    BlocksWidget *BlocksWidget::getInstance() {
        if (instance == nullptr) {
            instance = new BlocksWidget();
        }
        return instance;
    }

} // namespace Logicon
