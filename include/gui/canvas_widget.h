//
// Created by JMendyk on 28.12.17.
//

#ifndef LOGICON_CANVASWIDGET_H
#define LOGICON_CANVASWIDGET_H

#include "gui/gUtils.h"
#include "gui/gCircuit.h"
#include <memory>

namespace Logicon {

    // forward declaraton of parent
    class App;

    class CanvasWidget {

        App *app;
        std::shared_ptr<GCircuit> gCircuit;

      public:
        /**
         * Constructor accepting pointer to parent app.
         * @param parent parent app
         * @return true if initialization was successful
         */
        bool init(App *parent);

        void render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size);
        bool close();

        /**
         * Receive information from BlocksWidget which Gate should be placed in GCircuit
         * @param gate_type gate to place
         */
        void set_current_gate_to_place(GATE_TYPE gate_type);
    };

} // namespace Logicon

#endif //LOGICON_CANVASWIDGET_H
