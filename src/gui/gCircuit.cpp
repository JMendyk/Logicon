//
// Created by JMendyk on 28.12.17.
//

#include "gui/gCircuit.h"

#include <algorithm>
#include <gates/and.h> // TODO delete

namespace Logicon {

    GCircuit::GCircuit(std::shared_ptr<Circuit> circuit) : circuit(circuit) {}

    bool GCircuit::init() {

        // TODO: Remove hard-coded GBlock's when adding GBlock's will be possible

        assert(circuit != nullptr);

        auto g1 = std::make_shared<And>(Circuit::nextID());
        circuit->add(std::static_pointer_cast<Gate, And>(g1));
        auto g2 = std::make_shared<And>(Circuit::nextID());
        circuit->add(std::static_pointer_cast<Gate, And>(g2));
        auto g3 = std::make_shared<And>(Circuit::nextID());
        circuit->add(std::static_pointer_cast<Gate, And>(g3));
        auto g4 = std::make_shared<And>(Circuit::nextID());
        circuit->add(std::static_pointer_cast<Gate, And>(g4));

        circuit->connect(g1->id, 0, g2->id, 1);
        circuit->find(g1->id)->setOutputState(0, 1);
        circuit->find(g2->id)->setInputState(1, 1);
        circuit->connect(g3->id, 0, g2->id, 0);
        circuit->connect(g3->id, 0, g1->id, 0);
        circuit->connect(g2->id, 0, g4->id, 1);

        insert(g1, UI::Vec2(7, 6));
        insert(g2, UI::Vec2(15, 3));
        insert(g3, UI::Vec2(1, 1));
        insert(g4, UI::Vec2(20, 9));
        return true;
    }

    bool GCircuit::close() {
        // TODO: Check for potential memory leaks
        gBlocks.clear();
        // TODO: circuit.clear();
        return true;
    }

    const std::shared_ptr<Circuit> GCircuit::getCircuit() const {
        return circuit;
    }

    const GCircuit::_GBLOCK_CONTAINER_TYPE &GCircuit::getGBlocks() const {
        return gBlocks;
    };

    std::shared_ptr<GBlock> GCircuit::getGBlockAt(UI::Vec2 &pos) {
        UI::Vec2 gridPos = UI::toGridCoordinates(pos);
        auto found = std::find_if(
                gBlocks.begin(), gBlocks.end(),
                [gridPos](const std::shared_ptr<GBlock> &gBlock) { return gBlock->getRect().contains(gridPos); }
        );

        if (found == gBlocks.end())
            return nullptr;
        return *found;
    }

    std::shared_ptr<GBlock> GCircuit::getGBlockByID(ID &id) {
        auto found = std::find_if(gBlocks.begin(), gBlocks.end(),
                                  [id](const std::shared_ptr<GBlock> &gBlock) { return gBlock->getId() == id; }
        );

        if (found == gBlocks.end())
            return nullptr;
        return *found;
    }

    void GCircuit::insert(std::shared_ptr<Gate> gate, UI::Vec2 pos) {
        auto inserted = std::make_shared<GBlock>(shared_from_this(), gate, pos);
        gBlocks.push_back(inserted);
    }

    void GCircuit::remove(ID &id) {
        // TODO: Check for potential memory leaks
        auto found = std::find_if(gBlocks.begin(), gBlocks.end(),
                                  [id](const std::shared_ptr<GBlock> &gBlock) { return gBlock->getId() == id; }
        );
        if (found != gBlocks.end())
            gBlocks.erase(found);
    }

    void GCircuit::clear() {
        gBlocks.clear();
        // TODO: circuit->clear();
    }

    bool GCircuit::isOccupied(ID id, UI::Rect rect) {
        // Check for GBlock going out-of-bounds.
        // GCircuit's canvas is extending towards positive coordinates based on positions of GBlocks,
        // so we only check if GBlock stays in first quadrant of coordinate system.
        if (rect.getTopLeft().x < 0 || rect.getTopLeft().y < 0)
            return true;
        // TODO: spatial data struct for optimised collision checking. e.g. quad tree
        return std::find_if(
                gBlocks.begin(), gBlocks.end(),
                [&id, &rect](const std::shared_ptr<GBlock> &p) {
                    return p->getId() != id && p->getRect().overlaps(rect);
                }
        ) != gBlocks.end();
    }

    bool GCircuit::move(ID &id, UI::Vec2 pos) {
        // Maybe call isOccupied to make sure that no block overlapping will occur.
        auto found = getGBlockByID(id);
        if (found == nullptr)
            return false;
        if (isOccupied(id, found->getRect()))
            return false;
        found->move(pos);
        return true;
    }

    void GCircuit::connect(ID idFrom, Port output, ID idTo, Port input) {
        circuit->connect(idFrom, output, idTo, input);
    }

    void GCircuit::disconnect(ID idFrom, Port output, ID idTo, Port input) {
        circuit->disconnect(idFrom, output, idTo, input);
    }

    void GCircuit::update() {
        for (const auto &gBlock : gBlocks)
            gBlock->update();
    }

    void GCircuit::render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size) {
        ImGuiWindowFlags window_flags = 0
                                        | ImGuiWindowFlags_AlwaysVerticalScrollbar
                                        | ImGuiWindowFlags_AlwaysHorizontalScrollbar;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, UI::Vec2(0, 0));
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, UI::Vec2(0, 0));

        if (ImGui::BeginChild(ImGui::GetID("GCircuit"), window_size, false, window_flags)) {
            ImDrawList *dl = ImGui::GetWindowDrawList();
            const UI::Vec2 dl_origin = ImGui::GetWindowPos() + ImGui::GetWindowContentRegionMin();

            scrollCanvas();

            // TODO: Update content_size based on most right-bottom block's position
            static UI::Vec2 content_size = UI::Vec2(2048, 2048);

            // FIXME: This solution can be improved by only updating content_size if new GBlock is added or existing one was moved.
            std::for_each(gBlocks.begin(), gBlocks.end(), [](const std::shared_ptr<GBlock> &gBlock) {
                UI::Vec2 br = gBlock->getRect().getBottomRight();
                content_size.x = fmaxf(content_size.x, br.x);
                content_size.y = fmaxf(content_size.y, br.y);
            });

            static const UI::Vec2 canvas_botom_right_margin = ImVec2(128, 128);
            UI::Vec2 canvas_size = content_size + canvas_botom_right_margin;

            {
                // Render grid
                ImU32 GRID_COLOR = ImColor(200, 200, 200, 40);

                for (float x = 0; x < canvas_size.x; x += UI::CANVAS_GRID_SIZE)
                    dl->AddLine(UI::Vec2(x, 0.0f) + dl_origin, UI::Vec2(x, canvas_size.y) + dl_origin, GRID_COLOR);
                for (float y = 0; y < canvas_size.y; y += UI::CANVAS_GRID_SIZE)
                    dl->AddLine(UI::Vec2(0.0f, y) + dl_origin, UI::Vec2(canvas_size.x, y) + dl_origin, GRID_COLOR);
            }

            ImGui::GetWindowDrawList()->ChannelsSplit(UI::CANVAS_CHANNEL_COUNT);
            {
                /*
                 * Render gBlocks
                 */
                std::for_each(gBlocks.begin(), gBlocks.end(), [](const std::shared_ptr<GBlock> &gBlock) {
                    gBlock->render();
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

    // =====
    // LOCAL
    // =====

    void GCircuit::scrollCanvas() {
        UI::Vec2 scrolling = UI::Vec2(0.0f, 0.0f);
        static bool is_dragging = false;

        if ((ImGui::IsWindowHovered() || is_dragging) && !ImGui::IsAnyItemActive()) {
            // Scroll using middle mouse button
            if (ImGui::IsMouseDragging(2, 0.0f)) {
                scrolling = scrolling + ImGui::GetIO().MouseDelta;
                is_dragging = true;
            }

            if (ImGui::IsMouseReleased(2))
                is_dragging = false;

            if (ImGui::GetIO().KeyCtrl) {
                // TODO: Zooming? Maybe?
                // scale = scale + ImGui::GetIO().MouseWheel;
            } else {
                static float wheelSpeed = 64;
                if (!ImGui::GetIO().KeyShift) {
                    // Scroll vertically using mouse wheel
                    scrolling = scrolling + UI::Vec2(0, ImGui::GetIO().MouseWheel) * wheelSpeed;
                } else {
                    // Scroll horizontally using Shift + mouse wheel
                    scrolling = scrolling + UI::Vec2(ImGui::GetIO().MouseWheel, 0) * wheelSpeed;
                }
            }
        }

        UI::Vec2 offset = UI::Vec2(ImGui::GetScrollX(), ImGui::GetScrollY()) - scrolling;
        ImGui::SetScrollX(offset.x);
        ImGui::SetScrollY(offset.y);
    }


} // namespace Logicon