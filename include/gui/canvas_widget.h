//
// Created by JMendyk on 28.12.17.
//

#ifndef LOGICON_CANVASWIDGET_H
#define LOGICON_CANVASWIDGET_H

#include <gui/gHelpers.h>

namespace Logicon {

    class CanvasWidget {

      public:
        bool init();
        void render_ui(const UIVec2 &window_pos, const UIVec2 &window_size);
        bool close();
    };

} // namespace Logicon

#endif //LOGICON_CANVASWIDGET_H
