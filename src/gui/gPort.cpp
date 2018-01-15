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

    GPort::GPort(bool isInput, std::shared_ptr<GCircuit> parentGCircuit, ID gateId, Port port,
                 UI::Vec2 relativePosition) :
            isInput(isInput),
            parentGCircuit(parentGCircuit),
            gateId(gateId),
            port(port),
            relativePosition(relativePosition),
            GPORT_HOVERED_FLAG(false),
            GPORT_DRAGGED_FLAG(false) {
        uniqeElemId = "~" + std::to_string(gateId) + ":" + (isInput ? "I" : "O") + ":" + std::to_string(port);
    }

    void GPort::dragging() {

    }

    void GPort::render(const UI::Vec2 &gBlockPos, State state) {
        bool placementMode = BlocksWidget::getInstance().PLACEMENT_MODE;
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

        // DRAGGED FLAG
        if (GPORT_HOVERED_FLAG && ImGui::IsMouseDown(0)) {
            GPORT_DRAGGED_FLAG = true;
            GPORT_CURRENTLY_DRAGGED = uniqeElemId;
        }

        if (ImGui::IsMouseReleased(0)) {
            GPORT_DRAGGED_FLAG = false;
            GPORT_CURRENTLY_DRAGGED = UI::GPORT_NONE_HOVERED;
        }
        /// Hover actions FIXME: add smart pointer to parent and make use of gate instead of finding each time
        if (GPORT_HOVERED_FLAG) {
            auto connections = isInput ?
                               parentGCircuit.lock()->getCircuit()->getGateById(gateId)->getInputConnections(port) :
                               parentGCircuit.lock()->getCircuit()->getGateById(gateId)->getOutputConnections(port);
            // Show tooltip with connections
            if (!connections.empty()) {
                ImGui::BeginTooltip();
                ImGui::Text("Connections:");
                for (Connection connection : connections)
                    ImGui::Text("~%d:%d", connection.id, connection.port);
                ImGui::EndTooltip();
            }
            if (ImGui::IsMouseClicked(1)) { // Disconnect on RMB
                for (Connection connection : connections)
                    isInput ?
                    parentGCircuit.lock()->getCircuit()->disconnect(connection.id, connection.port, gateId, port) :
                    parentGCircuit.lock()->getCircuit()->disconnect(gateId, port, connection.id, connection.port);
            }
        }

        /// Send drag'n'drop payload
        if (!placementMode && ImGui::BeginDragDropSource()) {
            Connection *GPortDragData = new Connection(gateId, port);
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
                    parentGCircuit.lock()->getCircuit()->connect(data->id, data->port, gateId, port);
                else
                    parentGCircuit.lock()->getCircuit()->connect(gateId, port, data->id, data->port);
                delete (data);
            }
            ImGui::EndDragDropTarget();
        }

        ImGui::GetWindowPos() + ImGui::GetWindowContentRegionMin();
        ImGui::PopID();
    }

    UI::Rect Logicon::GPort::getRect() {
        return UI::Rect(relativePosition + UI::toGridCoordinates(UI::Vec2(UI::GPORT_PADDING, UI::GPORT_PADDING)),
                        relativePosition + UI::toGridCoordinates(UI::Vec2(UI::GPORT_PADDING, UI::GPORT_PADDING)) +
                        UI::toGridCoordinates(UI::Vec2(UI::GPORT_SIZE, UI::GPORT_SIZE))
        );
    }

    std::string GPort::getHovered() {
        return GPORT_CURRENTLY_HOVERED;
    }

    std::string GPort::getDragged() {
        return GPORT_CURRENTLY_DRAGGED;
    }
} // namespace Logicon