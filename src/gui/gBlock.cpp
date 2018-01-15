//
// Created by JMendyk on 29.12.17.
//

#include <assetLoader.h>
#include <gates/switch.h>
#include <gates/input.h>
#include <gui/blocks_widget.h>
#include <gates/clock.h>
#include <gates/delay.h>
#include "gui/gBlock.h"
#include "gui/gCircuit.h"

namespace Logicon {

    static ID GBLOCK_CURRENTLY_HOVERED = -1;    /// holds info about currently hovered gate ID (excluding port areas)
    static ID GBLOCK_CURRENTLY_DRAGGED = -1;    /// holds info about currently dragget gate ID
    static int GBLOCK_CLICK_BEGIN_ON_GBLOCK = -1;     /// true if dragging was started on any gblock: -1=unset 0=no 1 = yes

    GBlock::GBlock(std::shared_ptr<GCircuit> parentGCircuit, std::shared_ptr<Gate> gate, UI::Vec2 relativePosition) :
            parentGCircuit(parentGCircuit),
            gate(gate),
            position(relativePosition),
            GBLOCK_HOVERED_FLAG(false),
            GBLOCK_DRAGGED_FLAG(false),
            GBLOCK_CONTEXT_OPENED_FLAG(false) {

        color = UI::DEFAULT_GBLOCK_COLOR;
        // deduce type (rectangle or square) based on gate type
        this->dimension = UI::gBlockDimensions[gate->getGateType()];

        // initialize GPorts
        gInputs.resize(gateInputsCount[gate->getGateType()]);
        for (int inputIndex = 0; inputIndex < gateInputsCount[gate->getGateType()]; ++inputIndex)
            gInputs[inputIndex] = std::make_shared<GPort>(true, parentGCircuit, gate->id, inputIndex,
                                                          UI::gPortInputPositions[gate->getGateType()][inputIndex]);

        gOutputs.resize(gateOutputsCount[gate->getGateType()]);
        for (int outputIndex = 0; outputIndex < gateOutputsCount[gate->getGateType()]; ++outputIndex)
            gOutputs[outputIndex] = std::make_shared<GPort>(false, parentGCircuit, gate->id, outputIndex,
                                                            UI::gPortOutputPositions[gate->getGateType()][outputIndex]);

        // set image
        texture = AssetLoader::getGateTexture(gate->getGateType());
    }

    void GBlock::render() {
        assert(!parentGCircuit.expired());
        bool placementMode = BlocksWidget::getInstance().PLACEMENT_MODE;
        bool wasDragging = false;

        /// UPDATE INFO - texture, current holding position etc.
        texture = AssetLoader::getGateTexture(gate->getGateType());
        // Dragging GBlock - before rendering button to get rid of drawing lag
        if (GBLOCK_DRAGGED_FLAG) {
            if (ImGui::IsMouseDown(0)) { // LPM is down - drag block and check for proper place on grid
                dragDeltaExact = ImGui::GetMouseDragDelta(); // Add delta vector
                UI::Vec2 dragDeltaGrid = UI::toGridCoordinates(steppify(dragDeltaExact, UI::CANVAS_GRID_SIZE));

                if (GBLOCK_DRAGGED_FLAG) {
                    if (parentGCircuit.lock()->isOccupied(gate->id, getRect() + dragDeltaGrid)) // Color change
                        color = ImColor(255, 0, 0, 255); // RED
                    else
                        color = ImColor(0, 255, 0, 255); // GREEN
                }
            }
            if (ImGui::IsMouseReleased(0)) {
                wasDragging = true;
                UI::Vec2 dragDeltaGrid = UI::toGridCoordinates(steppify(dragDeltaExact, UI::CANVAS_GRID_SIZE));

                if (!parentGCircuit.lock()->isOccupied(gate->id, getRect() + dragDeltaGrid))
                    this->move(position + dragDeltaGrid); // override position

                dragDeltaExact = UI::Vec2(0, 0);
                color = UI::DEFAULT_GBLOCK_COLOR;
                GBLOCK_DRAGGED_FLAG = false;
                GBLOCK_CURRENTLY_DRAGGED = -1;
            }
        }

        /// RENDER GATE
        // If GBlock is dragged, we want it to draw above all other GBlocks
        ImGui::GetWindowDrawList()->ChannelsSetCurrent(
                GBLOCK_DRAGGED_FLAG ? UI::ACTIVE_GBLOCK_CHANNEL : UI::DEFAULT_GBLOCK_CHANNEL);
        ImGui::SetCursorPos(UI::toCanvasCoordinates(position) + dragDeltaExact);
        ImGui::PushID(gate->id);
        if (ImGui::ImageButton((ImTextureID) texture.textureId,
                               dimension * UI::CANVAS_GRID_SIZE,
                               UI::Vec2(0, 0), UI::Vec2(1, 1),
                               0,
                               ImColor(0, 0, 0, 0),
                               placementMode ? UI::DIMMED_GBLOCK_COLOR : color) // dim if in placement mode
            && !placementMode
            && !wasDragging) {
            wasDragging = false;
            gate->clickAction();
        }

        // Allow overlap for port buttons
        ImGui::SetItemAllowOverlap();

        /// FLAGS SETUP
        // set GBLOCK_CLICK_BEGIN_ON_GBLOCK
        if (ImGui::IsMouseDown(0)) {
            if (GBLOCK_CLICK_BEGIN_ON_GBLOCK == -1)
                GBLOCK_CLICK_BEGIN_ON_GBLOCK = GBLOCK_HOVERED_FLAG ? 1 : 0;
            else if (GBLOCK_HOVERED_FLAG)
                GBLOCK_CLICK_BEGIN_ON_GBLOCK = 1;
        }

        // unset GBLOCK_CLICK_BEGIN_ON_GBLOCK
        if (ImGui::IsMouseReleased(0)) {
            GBLOCK_CLICK_BEGIN_ON_GBLOCK = -1;
        }

        // Set DRAGGED flag
        if (ImGui::IsItemHovered()                              // if item is hovered...
            && GBLOCK_CURRENTLY_DRAGGED == -1                   // and if currently dragged is nothing...
            && GPort::getHovered() == UI::GPORT_NONE_HOVERED    // and no port is hovered...
            && GPort::getDragged() == UI::GPORT_NONE_HOVERED    // and no port is dragged...
            && ImGui::IsMouseDragging(0, 4.0)                   // and is dragging with minimal threshold of 4 pixels
            && GBLOCK_CLICK_BEGIN_ON_GBLOCK) {
            GBLOCK_DRAGGED_FLAG = true;
            GBLOCK_CURRENTLY_DRAGGED = gate->id;
        }

        // Set HOVERED flag
        if (GBLOCK_DRAGGED_FLAG                                         // if the block is dragged or
            || (ImGui::IsItemHovered()                                  //    is hovered...
                && GBLOCK_CURRENTLY_DRAGGED == -1                       //    and none other is dragged...
                && GPort::getHovered() == UI::GPORT_NONE_HOVERED)) {    //    and no port is hovered...
            GBLOCK_HOVERED_FLAG = true;
            GBLOCK_CURRENTLY_HOVERED = gate->id;
        }

        // unset HOVERED flag
        if (!ImGui::IsItemHovered()                                 // if no longer hovered or
            || GPort::getHovered() != UI::GPORT_NONE_HOVERED) {     // if any GPort hovered
            GBLOCK_HOVERED_FLAG = false;
            if (GBLOCK_CURRENTLY_HOVERED == gate->id)
                GBLOCK_CURRENTLY_HOVERED = -1;
        }

        /// TOOLTIP
        if (GBLOCK_HOVERED_FLAG) {
            ImGui::BeginTooltip();
            ImGui::Text("TYPE: %s", gateTypeNames[gate->getGateType()].c_str());
            ImGui::Text("ID: %d", getId());
            if (gate->getGateType() == Logicon::CLOCK) {
                auto ptr = std::static_pointer_cast<Clock, Gate>(gate);
                ImGui::Text("ON_PERIOD: %d", ptr->getOnPeriod());
                ImGui::Text("OFF_PERIOD: %d", ptr->getOffPeriod());
                ImGui::Text("PHASE: %d", ptr->getPhase());
            }
            if (gate->getGateType() == Logicon::DELAY) {
                auto ptr = std::static_pointer_cast<Delay, Gate>(gate);
                ImGui::Text("DELAY: %d", ptr->getDelay());
            }
            ImGui::EndTooltip();
        }

        /// CONTEXT MENU
        if (GBLOCK_HOVERED_FLAG && ImGui::IsMouseReleased(1))
            GBLOCK_CONTEXT_OPENED_FLAG = true;
        if (GBLOCK_CONTEXT_OPENED_FLAG) {
            if (ImGui::BeginPopupContextItem()) // When used after an item that has an ID (here the Button), we can skip providing an ID to BeginPopupContextItem().
            {
                if (ImGui::Button("remove")) {
                    parentGCircuit.lock()->postponedRemoval = getId();
                    GBLOCK_CONTEXT_OPENED_FLAG = false;
                }
                ImGui::EndPopup();
            }
        }

        /// RENDER WIRES
        // draw beziers from outputs only
        ImGui::GetWindowDrawList()->ChannelsSetCurrent(UI::DEFAULT_CONNECTION_CHANNEL);
        ImGui::PushID("wire_outputs");
        for (int output = 0; output < gate->getOutputsCount(); ++output)
            for (Connection connection : gate->getOutputConnections(output))
                renderWire(gOutputs[output], connection.id, connection.port);
        ImGui::PopID();

        ImGui::GetWindowDrawList()->ChannelsSetCurrent(
                GBLOCK_DRAGGED_FLAG ? UI::ACTIVE_GPORT_CHANNEL : UI::DEFAULT_GPORT_CHANNEL);

        /// RENDER PORTS
        // draw GPorts
        ImGui::PushID("gport_inputs");
        for (const auto &gInput : gInputs) {
            gInput->render(position + UI::toGridCoordinates(dragDeltaExact), gate->getInputState(gInput->port));
        }
        ImGui::PopID();

        ImGui::PushID("gport_outputs");
        for (auto gOutput : gOutputs) {
            gOutput->render(position + UI::toGridCoordinates(dragDeltaExact), gate->getOutputState(gOutput->port));
        }
        ImGui::PopID();

        ImGui::PopID(); // Pop's GBlock ID, *ALL GBLOCK GUI ELEMENTS MUST BE RENDERED BEFORE THIS LINE!*
        ImGui::GetWindowDrawList()->ChannelsSetCurrent(UI::DEFAULT_GBLOCK_CHANNEL);

        /// POSTPONED REMOVAL TRIGGER
    }

    // TODO: move to gPort
    void GBlock::renderWire(std::shared_ptr<GPort> thisGPort, ID otherId, Port otherPort) {
        /// TODO: fix double rendering
        bool isHigh = (bool) (thisGPort->isInput ? this->gate->getInputState(thisGPort->port)
                                                 : this->gate->getOutputState(thisGPort->port));

        auto otherGBlock = parentGCircuit.lock()->getGBlockByID(otherId);
        ImColor color = isHigh ? UI::ON_STATE_COLOR : UI::OFF_STATE_COLOR;

        // upper left corner of the window
        UI::Vec2 shift = ImGui::GetWindowPos() + ImGui::GetWindowContentRegionMin();

        UI::Vec2 begin(this->position + thisGPort->relativePosition);
        UI::Vec2 end(otherGBlock->position + otherGBlock->getGPort(!thisGPort->isInput, otherPort)->relativePosition);


        // center square
        shift = shift + UI::Vec2(UI::CANVAS_GRID_SIZE / 2, UI::CANVAS_GRID_SIZE / 2);

        begin = UI::toCanvasCoordinates(begin) + shift + dragDeltaExact;
        UI::Vec2 beginControl = begin + (thisGPort->isInput ?
                                         UI::Vec2(-UI::BEZIER_CONTROL_DISTANCE, 0) :
                                         UI::Vec2(UI::BEZIER_CONTROL_DISTANCE, 0));
        end = UI::toCanvasCoordinates(end) + shift + otherGBlock->getDragDeltaExact();
        UI::Vec2 endControl = end + (thisGPort->isInput ?
                                     UI::Vec2(UI::BEZIER_CONTROL_DISTANCE, 0) :
                                     UI::Vec2(-UI::BEZIER_CONTROL_DISTANCE, 0));

        ImGui::GetWindowDrawList()->AddBezierCurve(begin, beginControl, endControl, end, color, UI::BEZIER_THICKNESS,
                                                   UI::BEZIER_SEGMENTS);
    }

    const ID &GBlock::getId() const {
        return gate->id;
    }

    UI::Rect GBlock::getRect() const {
        return UI::Rect(position, position + dimension);
    }

    std::shared_ptr<GPort> GBlock::getGPort(bool isInput, Port port) {
        //TODO throw
        if (port < 0 || (isInput && port >= gate->getInputsCount()) || (!isInput && port >= gate->getOutputsCount()))
            return nullptr;
        return isInput ? gInputs[port] : gOutputs[port];
    }

    const std::shared_ptr<Gate> &GBlock::getGate() const {
        return gate;
    }

    const UI::Vec2 &GBlock::getPosition() const {
        return position;
    }

    const UI::Vec2 &GBlock::getDimension() const {
        return dimension;
    }

    void GBlock::move(const UI::Vec2 pos) {
        this->position = pos;
    }

    const UI::Vec2 &GBlock::getDragDeltaExact() const {
        return dragDeltaExact;
    }

} // namespace Logicon