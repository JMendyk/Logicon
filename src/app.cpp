//
// Created by rufus on 12.12.17.
//

#include "app.h"

#include <imgui_impl_glfw_gl3.h>
#include "assetLoader.h"
#include "logger.h"

namespace Logicon {

    std::string App::APP_TITLE = "Logicon";

    /*
     * create new empty circuit, set tickrate to hard 1000
     * TODO: move INITIALIZED/UNINITIALIZED state to Circuit.h, leave the rest in APP. (for serialization)
     */
    App::App() : tickrate(1000), state(State::PAUSED) {
        circuit = std::make_shared<Circuit>(Circuit::nextID());
    }

    bool App::init() { //TODO: Place all app related initialization like logger, assets etc. here

        // TODO: check for flag in init() for SHELL and GUI here instead of main
        // GL initialization
        glfwSetErrorCallback(
                [](int error, const char *description) { Logicon::Logger::err("Error %d: %s", error, description); });
        if (!glfwInit()) {
            Logger::err("Cannot initialize GLFW.");
            return false;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        this->window = glfwCreateWindow(1280, 720, App::APP_TITLE.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(this->window);
        glfwSwapInterval(1); // Enable vsync
        gl3wInit();

        // Setup ImGui binding
        ImGui_ImplGlfwGL3_Init(this->window, true);

        /*
         * Add default app font
         * This must happen before initialization of any other app components
         * since default app font must be defined as the first one.
         */
        ImGuiIO &io = ImGui::GetIO();
        static ImFontConfig defaultFontConfig = ImFontConfig();
        io.Fonts->AddFontFromFileTTF("assets/fonts/Roboto-Medium.ttf", 15.0f, &defaultFontConfig);

        ImGui::GetStyle().WindowRounding = 0.0f;

        // Load assets: images
        AssetLoader::loadAssets();

        // Widgets
        this->menuWidget = MenuWidget::getInstance();
        if (!this->menuWidget->init(this, this->window))
            return false;

        this->blocksWidget = BlocksWidget::getInstance();
        if (!this->blocksWidget->init(this, this->window))
            return false;

        this->canvasWidget = CanvasWidget::getInstance();
        if (!this->canvasWidget->init(this))
            return false;

        this->footerWidget = FooterWidget::getInstance();
        if (!this->footerWidget->init(this, this->window))
            return false;

        // TODO: operate on a fresh file called 'circuit' as if it was just created
        return true;
    }

    void App::run() {
        if (!init()) { // TODO: close parts that were opened successfully
            Logicon::Logger::err("Failed to initialize the app.");
            exit(-1);
        }

        // Main app loop
        while (!glfwWindowShouldClose(this->window)) {
            glfwPollEvents();
            ImGui_ImplGlfwGL3_NewFrame();

            // if (tickrate...) engine.calcLogic(this.canvasWidget.gCircuit.circuit)
            this->render();

            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui::Render();

            glfwSwapBuffers(window);
        }

        if (!close()) {
            Logicon::Logger::err("Failed to properly close the app.");
            exit(-1);
        }
    }

    void App::render() {
        int canvas_w, canvas_h;
        glfwGetFramebufferSize(window, &canvas_w, &canvas_h);

        // Menu Widget
        this->menuWidget->render({UI::MARGIN,
                                  UI::MARGIN},
                                 {canvas_w - 2 * UI::MARGIN - UI::BLOCKS_WIDGET_WIDTH - UI::MARGIN,
                                 UI::MENU_WIDGET_HEIGHT});
        // Blocks Widget
        this->blocksWidget->render({canvas_w - UI::MARGIN - UI::BLOCKS_WIDGET_WIDTH,
                                    UI::MARGIN},
                                   {UI::BLOCKS_WIDGET_WIDTH,
                                   canvas_h - (UI::MARGIN + UI::FOOTER_WIDGET_HEIGHT + UI::MARGIN)});

        // Canvas Widget
        this->canvasWidget->render({UI::MARGIN,
                                   UI::MARGIN + UI::MENU_WIDGET_HEIGHT + UI::MARGIN},
                                   {canvas_w - UI::MARGIN - UI::MARGIN - UI::BLOCKS_WIDGET_WIDTH - UI::MARGIN,
                                   canvas_h - UI::MARGIN - UI::MENU_WIDGET_HEIGHT - UI::MARGIN - UI::MARGIN -
                                   UI::FOOTER_WIDGET_HEIGHT});

        // Footer Widget
        this->footerWidget->render({0,
                                   (float) canvas_h - (UI::FOOTER_WIDGET_HEIGHT)},
                                   {(float) canvas_w,
                                   UI::FOOTER_WIDGET_HEIGHT});
    }

    bool App::close() {
        if (!this->menuWidget->close())
            return false;

        if (!this->blocksWidget->close())
            return false;

        if (!this->canvasWidget->close())
            return false;

        if (!this->footerWidget->close())
            return false;

        ImGui_ImplGlfwGL3_Shutdown();
        glfwTerminate();

        return true;
    }

    void App::set_current_gate_to_place(GATE_TYPE gate_type) {
        canvasWidget->set_current_gate_to_place(gate_type);
    }
} // namespace Logicon