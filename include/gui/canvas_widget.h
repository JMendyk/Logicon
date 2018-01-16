//
// Created by JMendyk on 28.12.17.
//

#ifndef LOGICON_CANVASWIDGET_H
#define LOGICON_CANVASWIDGET_H

#include "gui/gUtils.h"
#include "gui/gCircuit.h"
#include <memory>

namespace Logicon {

    class CanvasWidget {
        std::shared_ptr<GCircuit> gCircuit;

//-----------------------------------------------------------------------------
    private:
        CanvasWidget() = default;
    public:
        static CanvasWidget &getInstance();

        CanvasWidget(const CanvasWidget &) = delete;

        void operator=(const CanvasWidget &) = delete;
//-----------------------------------------------------------------------------
    public:

        const std::shared_ptr<GCircuit> &getGCircuit() const;

        /**
         * Constructor accepting pointer to parent app.
         * @param parent parent app
         * @return true if initialization was successful
         */
        bool init(std::shared_ptr<Circuit> circuit);

        void render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size);

        bool close();

        void setGCircuit(std::shared_ptr<GCircuit> gCircuit);

    };

} // namespace Logicon

#endif //LOGICON_CANVASWIDGET_H
