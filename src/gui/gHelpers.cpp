//
// Created by JMendyk on 29.12.17.
//

#include "gui/gHelpers.h"

namespace Logicon {

    UIVec2 steppify(UIVec2 vec, UIVec2 step) {
        return {
            roundf(vec.x / step.x) * step.x,
            roundf(vec.y / step.y) * step.y
        };
    }

    UIRect steppify(UIRect rect, UIVec2 step) {
        return {
            steppify(rect.Min, step),
            steppify(rect.Min, step) + rect.getSize()
        };
    }

}  // namespace Logicon