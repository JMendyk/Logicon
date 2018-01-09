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
        relativePosition(relativePosition) {
    uniqeElemId = std::to_string(gateId) + "###" + std::to_string(index);
}

void Logicon::GPort::dragging() {

}

void Logicon::GPort::render(const UI::Vec2 &gBlockPos) {
    ImGui::PushID(uniqeElemId.c_str());
    ImGui::SetCursorPos(
            UI::toCanvasCoordinates(gBlockPos + relativePosition) +
            UI::Vec2(UI::GPORT_PADDING, UI::GPORT_PADDING));
    std::string text = isInput ? "I" : "O";
    ImGui::Button(text.c_str(), UI::Vec2(UI::GPORT_SIZE, UI::GPORT_SIZE));
    if (ImGui::IsItemClicked(0) && ImGui::IsItemActive()) {
        /* DEBUG printf("dragging\n"); */
    }
    ImGui::PopID();

}

Logicon::UI::Rect Logicon::GPort::getRect() {
    return UI::Rect(relativePosition + UI::toGridCoordinates(UI::Vec2(UI::GPORT_PADDING, UI::GPORT_PADDING)),
                    relativePosition + UI::toGridCoordinates(UI::Vec2(UI::GPORT_PADDING, UI::GPORT_PADDING)) +
                    UI::toGridCoordinates(UI::Vec2(UI::GPORT_SIZE, UI::GPORT_SIZE))
    );
}
