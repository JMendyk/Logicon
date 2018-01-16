//
// Created by JMendyk on 28.12.17.
//

#include "gui/gCircuit.h"

#include <gates/and.h>
#include <assetLoader.h>
#include <gates/delay.h>
#include <gates/clock.h>
#include <gates/input.h>
#include <gates/switch.h>
#include <gates/not.h>
#include <gates/or.h>
#include <gates/xor.h>
#include <gates/nand.h>
#include <gates/nor.h>
#include <gates/xnor.h>
#include <gui/blocks_widget.h>
#include <gui/footer_widget.h>

namespace Logicon {

    GCircuit::GCircuit(std::shared_ptr<Circuit> circuit) : circuit(circuit),
                                                           POSTPONED_OPERATIONS(0),
                                                           postponedRemoveId(0),
                                                           postponedConnectFrom(0, 0),
                                                           postponedConnectTo(0, 0),
                                                           postponedDisconnectFrom(0, 0),
                                                           postponedDisconnectTo(0, 0) {}

    bool GCircuit::init() {
        assert(circuit != nullptr);
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

    std::shared_ptr<GBlock> GCircuit::getGBlockByID(ID id) {
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

    void GCircuit::remove(ID id) {
        POSTPONED_OPERATIONS |= POSTPONED_REMOVE;
        postponedRemoveId = id;
    }

    void GCircuit::clear() {
        POSTPONED_OPERATIONS |= POSTPONED_CLEAR;
    }

    void GCircuit::connect(ID idFrom, Port output, ID idTo, Port input) {
        POSTPONED_OPERATIONS |= POSTPONED_CONNECT;
        postponedConnectFrom = {idFrom, output};
        postponedConnectTo = {idTo, input};
    }

    void GCircuit::disconnect(ID idFrom, Port output, ID idTo, Port input) {
        POSTPONED_OPERATIONS |= POSTPONED_DISCONNECT;
        postponedDisconnectFrom = {idFrom, output};
        postponedDisconnectTo = {idTo, input};
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

    bool GCircuit::move(ID id, UI::Vec2 pos) {
        // Maybe call isOccupied to make sure that no block overlapping will occur.
        auto found = getGBlockByID(id);
        if (found == nullptr)
            return false;
        if (isOccupied(id, found->getRect()))
            return false;
        found->move(pos);
        return true;
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

            {
                UI::Vec2 hovered_grid_cell =
                        UI::toGridCoordinates(ImGui::GetMousePos() - dl_origin);

                std::string status_x = ImGui::IsWindowHovered() ? std::to_string((int) hovered_grid_cell.x) : "-";
                std::string status_y = ImGui::IsWindowHovered() ? std::to_string((int) hovered_grid_cell.y) : "-";

                FooterWidget::getInstance().pushStatus(status_x + " x " + status_y);
            }

            scrollCanvas();

            static UI::Vec2 content_size = UI::Vec2(2048, 2048);

            // FIXME: This solution can be improved by only updating content_size if new GBlock is added or existing one was moved.
            std::for_each(gBlocks.begin(), gBlocks.end(), [](const std::shared_ptr<GBlock> &gBlock) {
                UI::Vec2 br = UI::toCanvasCoordinates(gBlock->getRect().getBottomRight()) + gBlock->getDragDeltaExact();
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

            // Render gBlocks
            std::for_each(gBlocks.begin(), gBlocks.end(), [this](const std::shared_ptr<GBlock> &gBlock) {
                gBlock->render();
            });
            ImGui::GetWindowDrawList()->ChannelsMerge();

            /// TODO: move to BlocksWidget with overriding draw list of canvas...
            if (BlocksWidget::getInstance().PLACEMENT_MODE) {
                GATE_TYPE currentGateToPlace = BlocksWidget::getInstance().current_gate_to_place;
                Texture tex = AssetLoader::getGateTexture(currentGateToPlace);

                UI::Vec2 mouse_pos = ImGui::GetIO().MousePos;
                UI::Vec2 dimension;
                dimension = UI::gBlockDimensions[currentGateToPlace];

                UI::Vec2 top_left = steppify(mouse_pos - dl_origin - (dimension * UI::CANVAS_GRID_SIZE) / 2,
                                             UI::CANVAS_GRID_SIZE);

                UI::Rect rect(UI::toGridCoordinates(top_left), UI::toGridCoordinates(top_left) + dimension);

                ImColor color;
                if (isOccupied(2147483647, rect)) // Color
                    color = ImColor(255, 0, 0, 255); // RED
                else
                    color = ImColor(0, 255, 0, 255); // GREEN


                dimension = dimension * UI::CANVAS_GRID_SIZE;
                ImGui::SetCursorPos(top_left);
                if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(tex.textureId), dimension,
                                       UI::Vec2(0, 0), UI::Vec2(1, 1),
                                       0,
                                       ImColor(0, 0, 0, 0), color) &&
                    !isOccupied(-1, rect)) {


                    switch (currentGateToPlace) {

                        case NOT: {
                            auto g1 = std::make_shared<Not>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, Not>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                        case DELAY: {
                            auto g1 = std::make_shared<Delay>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, Delay>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                        case SWITCH_OFF: {
                            auto g1 = std::make_shared<Switch>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, Switch>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                        case AND: {
                            auto g1 = std::make_shared<And>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, And>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                        case OR: {
                            auto g1 = std::make_shared<Or>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, Or>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                        case XOR: {
                            auto g1 = std::make_shared<Xor>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, Xor>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                        case NAND: {
                            auto g1 = std::make_shared<Nand>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, Nand>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                        case NOR: {
                            auto g1 = std::make_shared<Nor>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, Nor>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                        case XNOR: {
                            auto g1 = std::make_shared<Xnor>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, Xnor>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                        case CLOCK: {
                            auto g1 = std::make_shared<Clock>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, Clock>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                        case INPUT_OFF: {
                            auto g1 = std::make_shared<Input>(Circuit::nextID());
                            circuit->add(std::static_pointer_cast<Gate, Input>(g1));
                            insert(g1, UI::toGridCoordinates(top_left));
                            break;
                        }
                    }
                }
            }

            ImGui::SetCursorPos(canvas_size);
        }
        ImGui::EndChild();
        ImGui::PopStyleVar(2);

        // Apply all modifications: removes, connects etc. etc.
        executePostponed();
    }

//-----------------------------------------------------------------------------
// INTERNAL
//-----------------------------------------------------------------------------

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

    void GCircuit::executePostponed() {
        // @formatter:off
        if (POSTPONED_OPERATIONS & POSTPONED_CONNECT)
            postponedConnect(postponedConnectFrom.id, postponedConnectFrom.port, postponedConnectTo.id, postponedConnectTo.port);
        if (POSTPONED_OPERATIONS & POSTPONED_DISCONNECT)
            postponedDisconnect(postponedConnectFrom.id, postponedConnectFrom.port, postponedConnectTo.id, postponedConnectTo.port);
        if (POSTPONED_OPERATIONS & POSTPONED_REMOVE)
            postponedRemove(postponedRemoveId);
        if (POSTPONED_OPERATIONS & POSTPONED_CLEAR)
            postponedClear();

        POSTPONED_OPERATIONS = 0;
        // @formatter:on
    }

    void GCircuit::postponedRemove(ID id) {
        // remove from graphical model
        auto found = std::find_if(gBlocks.begin(), gBlocks.end(),
                                  [id](const std::shared_ptr<GBlock> &gBlock) { return gBlock->getId() == id; });
        if (found != gBlocks.end())
            gBlocks.erase(found);
        // remove from model
        circuit->remove(id);
    }

    void GCircuit::postponedClear() {
        gBlocks.clear();
        circuit->clear();
    }

    void GCircuit::postponedConnect(ID idFrom, Port output, ID idTo, Port input) {
        circuit->connect(idFrom, output, idTo, input);
    }

    void GCircuit::postponedDisconnect(ID idFrom, Port output, ID idTo, Port input) {
        circuit->disconnect(idFrom, output, idTo, input);
    }


} // namespace Logicon