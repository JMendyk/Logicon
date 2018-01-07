//
// Created by JMendyk on 28.12.17.
//

#include "gui/gCircuit.h"

#include <algorithm>

namespace Logicon {

    bool GCircuit::init() {

        // TODO: Remove hard-coded GBlock's when adding GBlock's will be possible
        UIVec2 size = UIVec2(2 * UI::CANVAS_GRID_SIZE, UI::CANVAS_GRID_SIZE);
        Texture tex = load_texture("../assets/gblock_dummy.png");

        std::shared_ptr<GBlock> bl = std::make_shared<GBlock>(size, tex, Data());

        insert(UIVec2(3 * UI::CANVAS_GRID_SIZE, 3 * UI::CANVAS_GRID_SIZE), 0, std::make_shared<GBlock>(*bl));
        insert(UIVec2(7 * UI::CANVAS_GRID_SIZE, 6 * UI::CANVAS_GRID_SIZE), 1, std::make_shared<GBlock>(*bl));
        insert(UIVec2(12 * UI::CANVAS_GRID_SIZE, 6 * UI::CANVAS_GRID_SIZE), 2, std::make_shared<GBlock>(*bl));

        return true;
    }

    bool GCircuit::close() {
        // TODO: Check for potential memory leaks
        blocks.clear();
        connections.clear();
        return true;
    }

    void dragging() {
        UIVec2 scrolling = UIVec2(0.0f, 0.0f);
        static bool is_dragging = false;

        if ((ImGui::IsWindowHovered() || is_dragging) && !ImGui::IsAnyItemActive()) {
            // Scroll using middle mouse button
            if (ImGui::IsMouseDragging(2, 0.0f)) {
                scrolling = scrolling + ImGui::GetIO().MouseDelta;
                is_dragging = true;
            }

            if(ImGui::IsMouseReleased(2))
                is_dragging = false;

            if(ImGui::GetIO().KeyCtrl) {
                // TODO: Zooming? Maybe?
                // scale = scale + ImGui::GetIO().MouseWheel;
            } else {
                static float wheelSpeed = 64;
                if (!ImGui::GetIO().KeyShift) {
                    // Scroll vertically using mouse wheel
                    scrolling = scrolling + UIVec2(0, ImGui::GetIO().MouseWheel) * wheelSpeed;
                } else {
                    // Scroll horizontally using Shift + mouse wheel
                    scrolling = scrolling + UIVec2(ImGui::GetIO().MouseWheel, 0) * wheelSpeed;
                }
            }
        }

        UIVec2 offset = UIVec2(ImGui::GetScrollX(), ImGui::GetScrollY()) - scrolling;
        ImGui::SetScrollX(offset.x);
        ImGui::SetScrollY(offset.y);
    }

    void GCircuit::render_ui(const UIVec2 &window_pos, const UIVec2 &window_size) {
        ImGuiWindowFlags window_flags = 0
            | ImGuiWindowFlags_AlwaysVerticalScrollbar
            | ImGuiWindowFlags_AlwaysHorizontalScrollbar;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, UIVec2(0,0));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, UIVec2(0,0));

        if(ImGui::BeginChild(ImGui::GetID("GCircuit"), window_size, false, window_flags)) {
            ImDrawList *dl = ImGui::GetWindowDrawList();
            const UIVec2 dl_origin = ImGui::GetWindowPos() + ImGui::GetWindowContentRegionMin();

            dragging();


            static UIVec2 content_size = UIVec2(2048, 2048);

            // FIXME: This solution can be improved by only updating content_size if new GBlock is added or existing one was moved.
            std::for_each(blocks.begin(), blocks.end(), [](const std::pair<ID, std::shared_ptr<GBlock>> gBlock) {
              UIVec2 br = gBlock.second->getRect().getBR();
              content_size.x = fmaxf(content_size.x, br.x);
              content_size.y = fmaxf(content_size.y, br.y);
            });

            static const UIVec2 canvas_botom_right_margin = ImVec2(128, 128);
            UIVec2 canvas_size = content_size + canvas_botom_right_margin;

            {
                /*
                 * Render grid
                 */
                ImU32 GRID_COLOR = ImColor(200, 200, 200, 40);

                for (float x = 0; x < canvas_size.x; x += UI::CANVAS_GRID_SIZE)
                    dl->AddLine(UIVec2(x, 0.0f) + dl_origin, UIVec2(x, canvas_size.y) + dl_origin, GRID_COLOR);
                for (float y = 0; y < canvas_size.y; y += UI::CANVAS_GRID_SIZE)
                    dl->AddLine(UIVec2(0.0f, y) + dl_origin, UIVec2(canvas_size.x, y) + dl_origin, GRID_COLOR);
            }

            ImGui::GetWindowDrawList()->ChannelsSplit(UI::GCIRCUIT_CHANNELS_COUNT);
            {
                /*
                 * Render blocks
                 */
                std::for_each(blocks.begin(), blocks.end(), [](const std::pair<ID, std::shared_ptr<GBlock>> gBlock) {
                  gBlock.second->render();
                });

                /*
                 * TODO: Render connections (who will render them?)
                 */
            }
            ImGui::GetWindowDrawList()->ChannelsMerge();

            ImGui::SetCursorPos(canvas_size);
        }
        ImGui::EndChild();
        ImGui::PopStyleVar(2);
    }


    void GCircuit::insert(UIVec2 pos, ID id, std::shared_ptr<GBlock> gBlock) {
        gBlock->place(shared_from_this(), id, pos);
        blocks.insert(std::make_pair(id, gBlock));
    }

    void GCircuit::remove(ID gBlockID) {
        // TODO: Check for potential memory leaks
        auto gBlock_it = blocks.find(gBlockID);
        if(gBlock_it != blocks.end())
            blocks.erase(gBlock_it);
    }

    bool GCircuit::move(ID gBlockID, UIVec2 pos) {
        // TODO: Implement
        // Maybe call isOccupied to make sure that no block overlapping will occur.
        return true;
    }

    void GCircuit::connect(ID idFrom, Port output, ID idTo, Port input) {
        // TODO: Implement
    }

    void GCircuit::disconnect(ID idFrom, Port output, ID idTo, Port input) {
        // TODO: Implement
    }

    bool GCircuit::isOccupied(ID id, UIRect rect) {
        // Check for GBlock going out-of-bounds.
        // GCircuit's canvas is extending towards positive coordinates based on positions of GBlocks,
        // so we only check if GBlock stays in first quadrant of coordinate system.
        if(rect.getTL().x < 0 || rect.getTL().y < 0)
            return true;

        return std::find_if(
            blocks.begin(), blocks.end(),
            [&id, &rect] (const std::pair<ID, std::shared_ptr<GBlock>> &p) {
              return p.second->getId() != id && p.second->getRect().overlaps(rect);
            }
        ) != blocks.end();
    }

    ID GCircuit::getGBlockIDAt(UIVec2 pos) {
        auto gBlock_it = std::find_if(
            blocks.begin(), blocks.end(),
            [&pos] (const std::pair<ID, std::shared_ptr<GBlock>> &p) {
              return p.second->getRect().contains(pos);
            }
        );

        if(gBlock_it == blocks.end())
            return 0; // TODO: Return "NOT FOUND" id
        return gBlock_it->first;
    }

    std::shared_ptr<GBlock> GCircuit::getGBlockByID(ID gBlockID) {
        auto gBlock_it = blocks.find(gBlockID);

        if(gBlock_it == blocks.end())
            return nullptr;
        return gBlock_it->second;
    }

    std::pair<ID, Port> GCircuit::getPortAt(UIVec2 pos) {
        // TODO: Check if GBlock was found
        ID gBlockID = getGBlockIDAt(pos);
        // TODO: Handle case when there is no port at gives position
        return std::make_pair(gBlockID, blocks[gBlockID]->getPortAt(pos));
    };

    bool GCircuit::i_move(ID id, UIVec2 pos) {
        return move(id, pos);
    }

    bool GCircuit::i_isOccupied(ID id, UIRect rect) {
        return isOccupied(id, rect);
    }

} // namespace Logicon