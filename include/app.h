//
// Created by rufus on 12.12.17.
//

#ifndef LOGICON_APP_H
#define LOGICON_APP_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <string>

#include "types.h"

#include "gui/gHelpers.h"

#include "gui/menu_widget.h"
#include "gui/blocks_widget.h"
#include "gui/footer_widget.h"

namespace Logicon {

    /**
     * @brief Main app class.
     * Coordinates work between various components: menus, engine, canvas, circuit, parsers, data etc.
     * Main program loop is located in here.
     */
    class App {
        static std::string APP_TITLE;
        /*
         * Clock, Time, Engine, Canvas and GCircuit are temporarily commented-out
         * since they aren't implemented yet nor are they possible to compile in the current state.
         */
        //Clock clock;
        //Time tickrate;
        //Engine engine;

        MenuWidget menuWidget;
        BlocksWidget blocksWidget;
        FooterWidget footerWidget;
        //Canvas canvas;
        //
        //GCircuit gCircuit;

        enum State {
            UNINITIALIZED, RUNNING, PAUSED, STEP_BY_STEP
        };

        State state;

        GLFWwindow* window;

        /**
         * Called once by App::run when app starts
         * @return true if initialization was successful
         */
        bool init();

        /**
         * Called by App::run once per frame
         */
        void render_ui();

        /**
         * Called once by App::run when app is about to close
         * @return true if everything was closed successfuly
         */
        bool close();

        /**
         * @return next unique identifier
         */
        ID nextID();

    public:
        /**
         * Call to start the app.
         */
        void run();
    };

} // namespace Logicon


#endif //LOGICON_APP_H
