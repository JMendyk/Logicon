//
// Created by rufus on 11.12.17.
//

#include "gates/switch.h"

namespace Logicon {
    Switch::Switch(ID id, Circuit parent) : Gate(id, parent) {

    }

    void Switch::update() {

    }

    void Switch::clickAction() {
        Gate::clickAction();
    }
} // namespace Logicon