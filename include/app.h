//
// Created by rufus on 12.12.17.
//

#ifndef LOGICON_APP_H
#define LOGICON_APP_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "types.h"
#include "gui/gUtils.h"
#include <string>
#include <chrono>

#include "engine.h"
#include "circuit.h"

#include "gui/menu_widget.h"
#include "gui/blocks_widget.h"
#include "gui/canvas_widget.h"
#include "gui/footer_widget.h"

namespace Logicon {


    /**
     * @brief Main app class.
     * Coordinates work between various components: menus, engine, canvas, circuit, parsers, data etc.
     * Main program loop is located in here.
     */
    class App {


        GLFWwindow *window;                                             /// GL Window used as GUI root container

    public:
        Tick tickrate;                                                  /// how often engine calculates logic

        Engine *engine;                                                 /// Engine singleton
        std::shared_ptr<Circuit> circuit;                               /// current circuit
        int timer;
        float simulationSpeed;

        std::string APP_TITLE;
        MenuWidget *menuWidget;
        BlocksWidget *blocksWidget;
        FooterWidget *footerWidget;
        CanvasWidget *canvasWidget;

        enum STATE {                                        /// Represents current mode in which app is running TODO: Move UNINITIALIZED state inside CIRCUIT
            RUNNING,
            PAUSED,
            RESTART
        } state;

        bool STEP_NEXT_STEP;

        /// Constructor creates new Circuit
        App();

        /**
         * @brief Starts the app.
         */
        void run(bool shellMode);

    private:

        /**
         * @brief Initializes app - opens config, images, reads values from config, initializes public members
         * Called once by App::run when app starts
         * @return true if initialization was successful
         */
        bool init(bool shellMode);

        /**
         * @brief Simmilar to init() - closes proper files etc.
         * Called once by App::run when app is about to close
         * @return true if close was a success
         */
        bool close(bool shellMode);


        /**
         * @brief Initializes app for GUI mode
         * @return true if initialization was successful
         */
        bool initGui();

        /**
         * @brief Launch app in GUI mode
         */
        void runGUI();

        /**
         * @brief Renders imgui widgets.
         * Called by App::run once per frame
         */
        void render();

        /**
         * @brief Run when exiting the gui
         * @return true if close was a success
         */
        bool closeGui();

        /**
         * @brief Initializes app for Shell mode
         * @return true if initialization was successful
         */
        bool initShell();

        /**
         * @brief Launch app in shell mode
         */
        void runShell();

        /**
         * @brief Run when exiting the shell
         * @return true if close was a success
         */
        bool closeShell();
    };

} // namespace Logicon


#endif //LOGICON_APP_H
