//
// Created by rufus on 11.12.17.
//

#include "gates/input.h"

namespace Logicon {
    Input::Input(ID id) : Gate(GATE_TYPE::INPUT, id) {}


    void Input::update() {

    }

    void Input::clickAction() {
        Gate::clickAction();
    }
} // namespace Logicon