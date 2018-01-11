//
// Created by rufus on 12.12.17.
//

#ifndef LOGICON_APP_H
#define LOGICON_APP_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <string>

#include "types.h"

#include "gui/gUtils.h"

#include "gui/menu_widget.h"
#include "gui/blocks_widget.h"
#include <gui/canvas_widget.h>
#include "gui/footer_widget.h"

namespace Logicon {

    /**
     * @brief Main app class.
     * Coordinates work between various components: menus, engine, canvas, circuit, parsers, data etc.
     * Main program loop is located in here.
     */
    class App {
        //Clock clock;
        //Engine engine;

        /// GL Window used as GUI root container
        GLFWwindow *window;

    public:
        static std::string APP_TITLE;

        MenuWidget *menuWidget;
        BlocksWidget *blocksWidget;
        FooterWidget *footerWidget;
        CanvasWidget *canvasWidget;

        Tick tickrate;                                      /// how often engine calculates logic
        std::shared_ptr<Circuit> circuit;                   /// current circuit
        enum State {                                        /// Represents current mode in which app is running TODO: Move UNINITIALIZED state inside CIRCUIT
            UNINITIALIZED, RUNNING, PAUSED, STEP_BY_STEP
        } state;

        /// Constructor creates new Circuit
        App();

        /**
         * @brief Starts the app.
         */
        void run();

        /**
         * Receive information from BlocksWidget which Gate should be placed in GCircuit
         * @param gate_type gate to place
         */
        void set_current_gate_to_place(GATE_TYPE gate_type);

    private:

        /**
         * @brief Initializes app - opens config, images, reads values from config, initializes public members
         * Called once by App::run when app starts
         * @return true if initialization was successful
         */
        bool init();

        /**
         * @brief Renders imgui widgets.
         * Called by App::run once per frame
         */
        void render();

        /**
         * @brief Simmilar to init() - closes proper files etc.
         * Called once by App::run when app is about to close
         * @return true if everything was closed successfuly
         */
        bool close();
    };

} // namespace Logicon


#endif //LOGICON_APP_H
