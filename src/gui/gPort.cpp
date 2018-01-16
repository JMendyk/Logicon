//
// Created by Tooster on 2017-12-31.
//

#include <utility>
#include <gui/blocks_widget.h>
#include "gui/gPort.h"
#include "gui/gCircuit.h"

namespace Logicon {

    static std::string GPORT_CURRENTLY_HOVERED = UI::GPORT_NONE_HOVERED;
    static std::string GPORT_CURRENTLY_DRAGGED = UI::GPORT_NONE_HOVERED;
    static std::string GPORT_CLICK_BEGIN_ON_GPORT = "unset";

    GPort::GPort(std::shared_ptr<Logicon::GBlock> parentGBlock, bool isInput, Port port) :
            isInput(isInput),
            parentGBlock(parentGBlock),
            port(port),
            relativePosition(isInput ?
                             UI::gPortInputPositions[parentGBlock->getGate()->getGateType()][port] :
                             UI::gPortOutputPositions[parentGBlock->getGate()->getGateType()][port]),
            GPORT_HOVERED_FLAG(false),
            GPORT_DRAGGED_FLAG(false) {
        uniqeElemId =
                "~" + std::to_string(parentGBlock->getId()) + ":" + (isInput ? "I" : "O") + ":" + std::to_string(port);
    }

    void GPort::render() {
        bool placementMode = BlocksWidget::getInstance().PLACEMENT_MODE;
        UI::Vec2 gBlockPos =
                parentGBlock.lock()->getPosition() + UI::toGridCoordinates(parentGBlock.lock()->getDragDeltaExact());
        State state = isInput ?
                      parentGBlock.lock()->getGate()->getInputState(port) :
                      parentGBlock.lock()->getGate()->getOutputState(port);
        /// RENDER PORT
        ImGui::PushID(port);
        ImGui::SetCursorPos(UI::toCanvasCoordinates(gBlockPos + relativePosition) +
                            UI::Vec2(UI::GPORT_PADDING, UI::GPORT_PADDING));
        ImVec4 color = placementMode ? UI::DIMMED_GPORT_COLOR : (state == 1 ? UI::ON_STATE_COLOR : UI::OFF_STATE_COLOR);
        ImGui::PushStyleColor(ImGuiCol_Button, color);
        ImGui::Button("", UI::Vec2(UI::GPORT_SIZE, UI::GPORT_SIZE));
        ImGui::PopStyleColor(1);

        /// SET FLAGS
        // HOVERED FLAG
        if (ImGui::IsItemHovered()) {
            GPORT_HOVERED_FLAG = true;
            GPORT_CURRENTLY_HOVERED = uniqeElemId;
        } else {
            GPORT_HOVERED_FLAG = false;
            if (GPORT_CURRENTLY_HOVERED == uniqeElemId)
                GPORT_CURRENTLY_HOVERED = UI::GPORT_NONE_HOVERED;
        }

        /// DISPLAY TOOLTIP
        if (GPORT_HOVERED_FLAG) {
            auto connections = isInput ?
                               parentGBlock.lock()->getGate()->getInputConnections(port) :
                               parentGBlock.lock()->getGate()->getOutputConnections(port);
            // Show tooltip with connections
            ImGui::BeginTooltip();
            ImGui::Text("~%d:%s[%d]", parentGBlock.lock()->getId(), isInput ? "IN" : "OUT", port);
            if (!connections.empty()) {
                ImGui::Text("Connections:");
                for (Connection connection : connections)
                    ImGui::Text("~%d:%d", connection.id, connection.port);
            }
            ImGui::EndTooltip();
        }
        /// ERASE CONNECTIONS ON DEL+LMB
        if (GPORT_HOVERED_FLAG && ImGui::GetIO().KeysDown[UI::KEY_DELETE] && ImGui::IsMouseClicked(0)) { // DEL+LMB
            auto connections = isInput ?
                               parentGBlock.lock()->getGate()->getInputConnections(port) :
                               parentGBlock.lock()->getGate()->getOutputConnections(port);
            for (Connection connection : connections)
                isInput ?
                parentGBlock.lock()->getParentGCircuit().lock()->disconnect(connection.id, connection.port,
                                                                            parentGBlock.lock()->getId(), port) :
                parentGBlock.lock()->getParentGCircuit().lock()->disconnect(parentGBlock.lock()->getId(), port,
                                                                            connection.id, connection.port);
        }

        /// Send drag'n'drop payload
        if (!placementMode && ImGui::BeginDragDropSource()) {
            GPORT_DRAGGED_FLAG = true;
            GPORT_CURRENTLY_DRAGGED = uniqeElemId;
            Connection *GPortDragData = new Connection(parentGBlock.lock()->getId(), port);
            Connection **GPortDragDataPointer = &GPortDragData;

            //printf("send payload: %d %d local: %d %d\n", GPortDragData->id, GPortDragData->port, gateId, port);
            ImGui::SetDragDropPayload(isInput ? DRAGDROP_FROM_INPUT : DRAGDROP_FROM_OUTPUT,
                                      GPortDragDataPointer,
                                      sizeof(Connection));

            ImGui::EndDragDropSource();
        }

        /// Receive drag'n'drop payload - works only on succesful payload accept
        if (!placementMode && ImGui::BeginDragDropTarget()) {
            auto payload = ImGui::AcceptDragDropPayload(isInput ? DRAGDROP_FROM_OUTPUT : DRAGDROP_FROM_INPUT);
            if (payload != nullptr && payload->IsDelivery()) {
                auto *data = *((Connection **) payload->Data);
                //printf("got payload: %d %d local: %d %d\n", data->idFrom, data->output, gateId, port);
                if (isInput)
                    parentGBlock.lock()->getParentGCircuit().lock()->connect(data->id, data->port,
                                                                             parentGBlock.lock()->getId(), port);
                else
                    parentGBlock.lock()->getParentGCircuit().lock()->connect(parentGBlock.lock()->getId(), port,
                                                                             data->id, data->port);
                delete (data);
            }
            ImGui::EndDragDropTarget();
            GPORT_DRAGGED_FLAG = false;
            GPORT_CURRENTLY_DRAGGED = UI::GPORT_NONE_HOVERED;
        }

        ImGui::GetWindowPos() + ImGui::GetWindowContentRegionMin();
        ImGui::PopID();
    }

    std::string GPort::getHovered() {
        return GPORT_CURRENTLY_HOVERED;
    }

    std::string GPort::getDragged() {
        return GPORT_CURRENTLY_DRAGGED;
    }
} // namespace Logicon