//
// Created by JMendyk on 29.12.17.
//

#include <assetLoader.h>
#include <gates/switch.h>
#include "gui/gBlock.h"
#include "gui/gCircuit.h"

namespace Logicon {

    GBlock::GBlock(std::shared_ptr<GCircuit> parentCircuit, std::shared_ptr<Gate> gate, UI::Vec2 relativePosition) :
            parentCircuit(parentCircuit), gate(gate), position(relativePosition), DRAGGING_FLAG(false) {

        // deduce type (rectangle or square) based on gate type
        if (gate->gateType <= Logicon::XNOR)
            this->dimension = UI::Vec2(5, 3);
        else
            this->dimension = UI::Vec2(3, 3);

        // initialize GPorts
        gInputs.resize(gateInputsCount[gate->gateType]);
        for (int inputIndex = 0; inputIndex < gateInputsCount[gate->gateType]; ++inputIndex)
            gInputs[inputIndex] = std::make_shared<GPort>(true, parentCircuit, gate->id, inputIndex,
                                                          UI::gPortInputPositions[gate->gateType][inputIndex]);

        gOutptus.resize(gateOutputsCount[gate->gateType]);
        for (int outputIndex = 0; outputIndex < gateOutputsCount[gate->gateType]; ++outputIndex)
            gOutptus[outputIndex] = std::make_shared<GPort>(false, parentCircuit, gate->id, outputIndex,
                                                            UI::gPortOutputPositions[gate->gateType][outputIndex]);

        // set image
        switch (gate->gateType) {

            case NOT:
                texture = Logicon::AssetLoader::gate_not();
                break;
            case DELAY:
                texture = Logicon::AssetLoader::gate_delay();
                break;
            case SWITCH:
                texture = Logicon::AssetLoader::gate_switch_off();
                break;
            case AND:
                texture = Logicon::AssetLoader::gate_and();
                break;
            case OR:
                texture = Logicon::AssetLoader::gate_or();
                break;
            case XOR:
                texture = Logicon::AssetLoader::gate_xor();
                break;
            case NAND:
                texture = Logicon::AssetLoader::gate_nand();
                break;
            case NOR:
                texture = Logicon::AssetLoader::gate_nor();
                break;
            case XNOR:
                texture = Logicon::AssetLoader::gate_xnor();
                break;
            case CLOCK:
                texture = Logicon::AssetLoader::gate_clock();
                break;
            case INPUT:
                texture = Logicon::AssetLoader::gate_input_low();
                break;
        }
    }


    void GBlock::render(bool should_interact) {
        ImColor color(255, 255, 255);

        assert(!parentCircuit.expired());


        // Dragging GBlock
        if (DRAGGING_FLAG) {
            if (ImGui::IsMouseDown(0)) { // LPM is down
                dragDeltaExact = ImGui::GetMouseDragDelta(); // Add delta vector
                UI::Vec2 dragDeltaGrid = UI::toGridCoordinates(steppify(dragDeltaExact, UI::CANVAS_GRID_SIZE));

                if (parentCircuit.lock()->isOccupied(gate->id, getRect() + dragDeltaGrid)) // Color
                    color = ImColor(255, 0, 0, 255); // RED
                else
                    color = ImColor(0, 255, 0, 255); // GREEN
            }
            if (ImGui::IsMouseReleased(0)) {
                UI::Vec2 dragDeltaGrid = UI::toGridCoordinates(steppify(dragDeltaExact, UI::CANVAS_GRID_SIZE));

                if (!parentCircuit.lock()->isOccupied(gate->id, getRect() + dragDeltaGrid))
                    this->move(position + dragDeltaGrid); // override position

                dragDeltaExact = UI::Vec2(0, 0);
                DRAGGING_FLAG = false;
            }
        }

        ImGui::PushID(gate->id);

        // If GBlock is dragged, we want it to draw above all other GBlocks
        ImGui::GetWindowDrawList()->ChannelsSetCurrent(
                DRAGGING_FLAG ? UI::ACTIVE_GBLOCK_CHANNEL : UI::DEFAULT_GBLOCK_CHANNEL);

        // Rendering GBlock
        ImGui::SetCursorPos(UI::toCanvasCoordinates(position) + dragDeltaExact);
        if (ImGui::ImageButton((ImTextureID) texture.textureId,
                               dimension * UI::CANVAS_GRID_SIZE,
                               UI::Vec2(0, 0),
                               UI::Vec2(1, 1),
                               0,
                               ImColor(0, 0, 0, 0),
                               color) && should_interact) {
            // TODO clickAction
        }

        // Allow overlap for port buttons
        ImGui::SetItemAllowOverlap();


        // draw beziers from outputs only
        ImGui::PushID("wire_outputs");
        for (int output = 0; output < gate->getOutputsCount(); ++output)
            for (Connection connection : gate->getOutputConnections(output))
                renderWire(gOutptus[output], connection.id, connection.port);
        ImGui::PopID();

        // IsItemHovered doesn't check what is at the top of mouse cursor - it may be GPort
        bool mouse_is_clicked_over_me = false;
        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0) && should_interact) {
            mouse_is_clicked_over_me = true;
            //dragDeltaExact = position;
        }

        ImGui::GetWindowDrawList()->ChannelsSetCurrent(
                DRAGGING_FLAG ? UI::ACTIVE_GPORT_CHANNEL : UI::DEFAULT_GPORT_CHANNEL);

        bool is_any_gport_dragged = false;

        // draw GPorts
        ImGui::PushID("gport_inputs");
        for (auto gInput : gInputs) {
            gInput->render(position + UI::toGridCoordinates(dragDeltaExact), should_interact);
            is_any_gport_dragged |= gInput->isDragged();
        }
        ImGui::PopID();

        ImGui::PushID("gport_outputs");
        for (auto gOutput : gOutptus) {
            gOutput->render(position + UI::toGridCoordinates(dragDeltaExact), should_interact);
            is_any_gport_dragged |= gOutput->isDragged();
        }
        ImGui::PopID();

        if(mouse_is_clicked_over_me && !is_any_gport_dragged) {
            DRAGGING_FLAG = true;
        }

        //ImGui::EndGroup();
        ImGui::PopID(); // Pop's GBlock ID, *ALL GBLOCK GUI ELEMENTS MUST BE RENDERED BEFORE THIS LINE!*
        ImGui::GetWindowDrawList()->ChannelsSetCurrent(UI::DEFAULT_GBLOCK_CHANNEL);
    }

    // TODO: move to gPort
    void GBlock::renderWire(std::shared_ptr<GPort> thisGPort, ID otherId, Port otherPort) {
        /// TODO: fix double rendering
        bool isHigh = (bool) (thisGPort->isInput ? this->gate->getInputState(thisGPort->port)
                                                 : this->gate->getOutputState(
                        thisGPort->port));

        auto otherGBlock = parentCircuit.lock()->getGBlockByID(otherId);

        ImColor color = isHigh ? ImColor(255, 195, 17) : ImColor(68, 74, 121);

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
        return isInput ? gInputs[port] : gOutptus[port];
    }

    // TODO: test the function
    std::shared_ptr<GPort> GBlock::getGPortAt(UI::Vec2 &pos) const {
        UI::Vec2 gridPos = UI::toGridCoordinates(pos);
        if (!this->getRect().contains(gridPos))
            return nullptr;
        for (auto gPort : gInputs)
            if (gPort->getRect().contains(gridPos))
                return gPort;
        return nullptr;
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

    void GBlock::update() {
        if (gate->gateType == SWITCH) {
            // cast(parent->getCircuit()->find(this->id))->isOn == true ... texture = switch_on ...
        } else if (gate->gateType == INPUT) {
            // std::static_pointer_cast<Logicon::Switch>(parent->getCircuit()->find(this->id))->isOn() ? texture = ... :
        }
        // TODO: Implement
    }

    bool GBlock::isDragged() const {
        return DRAGGING_FLAG;
    }

    const UI::Vec2 &GBlock::getDragDeltaExact() const {
        return dragDeltaExact;
    }

} // namespace Logicon