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

    BlocksWidget &BlocksWidget::getInstance() {
        static BlocksWidget instance;
        return instance;
    }
//-----------------------------------------------------------------------------

    bool BlocksWidget::init() {
        PLACEMENT_MODE = false;
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

            static auto set_current_gate_to_place = [this](GATE_TYPE gate_type) {
                if (gate_type == current_gate_to_place) {
                    PLACEMENT_MODE = false;
                } else {
                    PLACEMENT_MODE = true;
                    current_gate_to_place = gate_type;
                }
            };

            for (int gateType = 0; gateType < GATE_TYPE_COUNT; ++gateType) {
                if (gateType != Logicon::SWITCH_ON && gateType != Logicon::INPUT_ON) {
                    ImGui::PushID(gateType);
                    float height = size / (5.0f / 3);

                    Texture tex = AssetLoader::getGateTexture((GATE_TYPE) gateType);
                    if (ImGui::ImageButton(
                            reinterpret_cast<ImTextureID>(tex.textureId),
                            UI::Vec2(height * ((float) tex.width) / tex.height, height),
                            UI::Vec2(0, 0), UI::Vec2(1, 1),
                            0, ImColor(0, 0, 0, 0),
                            (PLACEMENT_MODE && current_gate_to_place == gateType) ?
                            ImColor(128, 128, 128, 200) :
                            ImColor(255, 255, 255, 200))) {
                        PLACEMENT_MODE = !PLACEMENT_MODE;
                        current_gate_to_place = (GATE_TYPE) (gateType);
                    }
                    ImGui::Spacing();
                    ImGui::NextColumn();
                    ImGui::PopID();
                }
            }

        }
        ImGui::EndGroup();
        ImGui::End();
    }

} // namespace Logicon
