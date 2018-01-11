//
// Created by Tooster on 2017-12-31.
//

#include <utility>

#include "gui/gPort.h"
#include "gui/gCircuit.h"

Logicon::GPort::GPort(bool isInput, std::shared_ptr<GCircuit> parentCircuit, ID gateId, Port index,
                      UI::Vec2 relativePosition) :
        isInput(isInput),
        parentCircuit(parentCircuit),
        gateId(gateId),
        index(index),
        relativePosition(relativePosition),
        DRAGGING_FLAG(false) {
    uniqeElemId = std::to_string(gateId) + "###" + std::to_string(isInput) + "###" + std::to_string(index);
}

void Logicon::GPort::dragging() {

}

void Logicon::GPort::render(const UI::Vec2 &gBlockPos, bool should_interact) {
    ImGui::PushID(index);

    ImGui::SetCursorPos(
            UI::toCanvasCoordinates(gBlockPos + relativePosition) +
            UI::Vec2(UI::GPORT_PADDING, UI::GPORT_PADDING));
    std::string text = isInput ? "I" : "O";
    if(ImGui::Button(text.c_str(), UI::Vec2(UI::GPORT_SIZE, UI::GPORT_SIZE)) && should_interact);

    DRAGGING_FLAG = ImGui::IsItemHovered() && ImGui::IsMouseClicked(0) && should_interact;

    struct GPortDragDropData { ID idFrom; Port output; };
    
    if(should_interact && ImGui::BeginDragDropSource()) {
        GPortDragDropData* gport_cp = new GPortDragDropData({ gateId, index });

        ImGui::SetDragDropPayload(isInput ? DRAGDROP_FROM_INPUT : DRAGDROP_FROM_OUTPUT, gport_cp, sizeof(gport_cp));

        ImGui::EndDragDropSource();
    }

    if(should_interact && ImGui::BeginDragDropTarget()) {
        auto payload = ImGui::AcceptDragDropPayload(!isInput ? DRAGDROP_FROM_INPUT : DRAGDROP_FROM_OUTPUT);
        if(payload != nullptr && payload->IsDelivery()) {
            auto *data = (GPortDragDropData *) payload->Data;

            if(isInput) {
                parentCircuit.lock()->connect(data->idFrom, data->output, gateId, index);
            } else {
                parentCircuit.lock()->connect(gateId, index, data->idFrom, data->output);
            }
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
