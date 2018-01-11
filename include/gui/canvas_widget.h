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
        static CanvasWidget *instance;
        App *app;
        std::shared_ptr<GCircuit> gCircuit;


    private:

        CanvasWidget() = default;

    public:

        static CanvasWidget *getInstance();

        const std::shared_ptr<GCircuit> &getGCircuit() const;

        /**
         * Constructor accepting pointer to parent app.
         * @param parent parent app
         * @return true if initialization was successful
         */
        bool init(App *parent);

        void render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size);

        bool close();

        void setGCircuit(const std::shared_ptr<Circuit> circuit);

    };

} // namespace Logicon

#endif //LOGICON_CANVASWIDGET_H
