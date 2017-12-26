//
// Created by rufus on 11.12.17.
//

#include "gates/switch.h"

namespace Logicon {
    Switch::Switch(ID id) : Gate(id, 1, 1) {}

    void Switch::update() {

    }

    void Switch::clickAction() {
        Gate::clickAction();
    }
} // namespace Logicon