//
// Created by Tooster on 2017-12-31.
//

#include <utility>

#include "gui/gPort.h"
#include "gui/gCircuit.h"

Logicon::GPort::GPort(bool isInput, std::shared_ptr<GCircuit> parentGCircuit, ID gateId, Port port,
                      UI::Vec2 relativePosition) :
        isInput(isInput),
        parentGCircuit(parentGCircuit),
        gateId(gateId),
        port(port),
        relativePosition(relativePosition),
        DRAGGING_FLAG(false) {
    uniqeElemId = std::to_string(gateId) + "###" + std::to_string(isInput) + "###" + std::to_string(port);
}

void Logicon::GPort::dragging() {

}

void Logicon::GPort::render(const UI::Vec2 &gBlockPos, bool should_interact) {
    ImGui::PushID(port);

    ImGui::SetCursorPos(
            UI::toCanvasCoordinates(gBlockPos + relativePosition) +
            UI::Vec2(UI::GPORT_PADDING, UI::GPORT_PADDING));
    std::string text = isInput ? "I" : "O";
    if (ImGui::Button(text.c_str(), UI::Vec2(UI::GPORT_SIZE, UI::GPORT_SIZE)) && should_interact);

    DRAGGING_FLAG = ImGui::IsItemHovered() && ImGui::IsMouseClicked(0) && should_interact;

    // Disconnect on RMB
    if (should_interact && ImGui::IsItemHovered() && ImGui::IsMouseClicked(1)) {
        auto connections = isInput ?
                           parentGCircuit.lock()->getCircuit()->getGateById(gateId)->getInputConnections(port) :
                           parentGCircuit.lock()->getCircuit()->getGateById(gateId)->getOutputConnections(port);
        for (Connection connection : connections)
            isInput ?
            parentGCircuit.lock()->disconnect(connection.id, connection.port, gateId, port) :
            parentGCircuit.lock()->disconnect(gateId, port, connection.id, connection.port);
    }

    struct GPortDragDropData {
        ID idFrom;
        Port output;
    };

    if (should_interact && ImGui::BeginDragDropSource()) {
        GPortDragDropData *gport_cp = new GPortDragDropData({gateId, port});

        GPortDragDropData **gport_cp_ptr = &gport_cp;

        //printf("send payload: %d %d local: %d %d\n", gport_cp->idFrom, gport_cp->output, gateId, port);
        ImGui::SetDragDropPayload(isInput ? DRAGDROP_FROM_INPUT : DRAGDROP_FROM_OUTPUT, gport_cp_ptr,
                                  sizeof(gport_cp_ptr));

        ImGui::EndDragDropSource();
    }

    if (should_interact && ImGui::BeginDragDropTarget()) {
        auto payload = ImGui::AcceptDragDropPayload(isInput ? DRAGDROP_FROM_OUTPUT : DRAGDROP_FROM_INPUT);
        if (payload != nullptr && payload->IsDelivery()) {
            auto *data = *((GPortDragDropData **) payload->Data);
            //printf("got payload: %d %d local: %d %d\n", data->idFrom, data->output, gateId, port);
            if (isInput) {
                parentGCircuit.lock()->connect(data->idFrom, data->output, gateId, port);
            } else {
                parentGCircuit.lock()->connect(gateId, port, data->idFrom, data->output);
            }
            delete (data);
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::PopID();
}

Logicon::UI::Rect Logicon::GPort::getRect() {
    return UI::Rect(relativePosition + UI::toGridCoordinates(UI::Vec2(UI::GPORT_PADDING, UI::GPORT_PADDING)),
                    relativePosition + UI::toGridCoordinates(UI::Vec2(UI::GPORT_PADDING, UI::GPORT_PADDING)) +
                    UI::toGridCoordinates(UI::Vec2(UI::GPORT_SIZE, UI::GPORT_SIZE))
    );
}

bool Logicon::GPort::isDragged() const {
    return DRAGGING_FLAG;
}
