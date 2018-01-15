//
// Created by rufus on 12.12.17.
//

#include "app.h"

#include <imgui_impl_glfw_gl3.h>
#include "assetLoader.h"
#include "logger.h"
#include <gates/and.h>
#include <gates/clock.h>
#include <gates/delay.h>
#include <gates/input.h>
#include <gates/nand.h>
#include <gates/nor.h>
#include <gates/not.h>
#include <gates/or.h>
#include <gates/switch.h>
#include <gates/xnor.h>
#include <gates/xor.h>

namespace Logicon {


    App &App::getInstance() {
        static App instance;
        return instance;
    }

//-----------------------------------------------------------------------------

    void App::run(bool shellMode) {
        if (!init())
            exit(1);
        if (shellMode) { // SHELL
            if (!initShell()) {
                Logicon::Logger::err("Couldn't initialize Logicon in shell mode.");
                exit(10);
            }
            runShell();
            if (!closeShell()) {
                Logicon::Logger::err("Couldn't properly close Logicon in shell mode");
                exit(30);
            }
        } else {
            if (!initGui()) { // GUI
                Logicon::Logger::err("Couldn't initialize Logicon in GUI mode.");
                exit(100);
            }
            runGUI();
            if (!closeGui()) {
                Logicon::Logger::err("Couldn't properly close Logicon in GUI mode");
                exit(300);
            }
        }
        if (!close())
            exit(3);
    }

//-----------------------------------------------------------------------------

    bool App::init() {
        APP_TITLE = "Logicon";
        Logicon::Logger::init();
        Logicon::Logger::info("Logicon started.");
        circuit = std::make_shared<Circuit>(Circuit::nextID());
        return true;
    }

    bool App::close() {
        Logicon::Logger::info("Logicon stoped.");
        return true;
    }

//-----------------------------------------------------------------------------
// SHELL
//-----------------------------------------------------------------------------

    bool App::initShell() {
        Logicon::Logger::info("MODE:   Shell");
        return true;
    }

    void App::runShell() {
        std::cout << "commands: " << std::endl;
        std::cout << "   exit, info, add, connect, disconnect, set, reset, clear," << std::endl;
        std::cout << "   propagate, restart, calculate, changeClock, changeDelay, update, click" << std::endl;
        std::cout << "gates: " << std::endl;
        std::cout << "   AND, CLOCK, DELAY, INPUT, NAND, NOR, OR, SWITCH, NOT, XNOR, XOR" << std::endl;
        std::cout << "WARNING: BEFORE CALCULATE AND AFTER EACH GRAPH CHANGE RUN RESTART" << std::endl;
        while (true) {
            std::string cmd;
            std::cin >> cmd;
            if (cmd == "exit")
                return;
            else if (cmd == "info") {
                auto gates = circuit->getGates();
                if (gates.empty())
                    std::cout << "circuit is empty" << std::endl;
                else {
                    std::cout << "================" << std::endl;
                    for (const auto &gate : gates)
                        [](const std::shared_ptr<Gate> &gate) -> void {
                            std::string gateType;
                            if (gate->getGateType() == Logicon::AND)
                                gateType = "AND";
                            else if (gate->getGateType() == Logicon::CLOCK)
                                gateType = "CLOCK";
                            else if (gate->getGateType() == Logicon::DELAY)
                                gateType = "DELAY";
                            else if (gate->getGateType() == Logicon::INPUT_ON ||
                                     gate->getGateType() == Logicon::INPUT_OFF)
                                gateType = "INPUT";
                            else if (gate->getGateType() == Logicon::NAND)
                                gateType = "NAND";
                            else if (gate->getGateType() == Logicon::NOR)
                                gateType = "NOR";
                            else if (gate->getGateType() == Logicon::NOT)
                                gateType = "NOT";
                            else if (gate->getGateType() == Logicon::OR)
                                gateType = "OR";
                            else if (gate->getGateType() == Logicon::SWITCH_ON ||
                                     gate->getGateType() == Logicon::SWITCH_OFF)
                                gateType = "SWITCH";
                            else if (gate->getGateType() == Logicon::XNOR)
                                gateType = "XNOR";
                            else if (gate->getGateType() == Logicon::XOR)
                                gateType = "XOR";


                            std::cout << gateType << "~" << gate->id << " ";
                            for (Port i = 0; i < gate->getInputsCount(); ++i) {
                                std::cout << "I[" << i << "]=(" << gate->getInputState(i) << "){ ";
                                auto inputs = gate->getInputConnections(i);
                                for (auto &input : inputs)
                                    std::cout << "#" << input.id << ":" << input.port << "  ";
                                std::cout << "} ";
                            }
                            for (Port i = 0; i < gate->getOutputsCount(); ++i) {
                                std::cout << "O[" << i << "]=(" << gate->getOutputState(i) << "){ ";
                                auto outputs = gate->getOutputConnections(i);
                                for (auto &output : outputs)
                                    std::cout << "#~" << output.id << ":" << output.port << "  ";
                                std::cout << "} ";
                            }
                            std::cout << std::endl;
                        };

                    std::cout << "================" << std::endl;
                }
            } else if (cmd == "add") {
                std::string type;
                std::cin >> type;
                if (type == "AND") {
                    auto ptr = std::make_shared<And>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, And>(ptr));
                } else if (type == "CLOCK") {
                    auto ptr = std::make_shared<Clock>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, Clock>(ptr));
                } else if (type == "DELAY") {
                    auto ptr = std::make_shared<Delay>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, Delay>(ptr));
                } else if (type == "INPUT") {
                    auto ptr = std::make_shared<Input>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, Input>(ptr));
                } else if (type == "NAND") {
                    auto ptr = std::make_shared<Nand>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, Nand>(ptr));
                } else if (type == "NOR") {
                    auto ptr = std::make_shared<Nor>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, Nor>(ptr));
                } else if (type == "OR") {
                    auto ptr = std::make_shared<Or>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, Or>(ptr));
                } else if (type == "SWITCH") {
                    auto ptr = std::make_shared<Switch>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, Switch>(ptr));
                } else if (type == "NOT") {
                    auto ptr = std::make_shared<Not>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, Not>(ptr));
                } else if (type == "XNOR") {
                    auto ptr = std::make_shared<Xnor>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, Xnor>(ptr));
                } else if (type == "XOR") {
                    auto ptr = std::make_shared<Xor>(Circuit::nextID());
                    circuit->add(std::static_pointer_cast<Gate, Xor>(ptr));
                }

            } else if (cmd == "remove") {
                ID id;
                std::cin >> id;

                circuit->remove(id);
            } else if (cmd == "connect") {
                ID ID1, ID2;
                Port output, input;
                std::cin >> ID1 >> output >> ID2 >> input;
                circuit->connect(ID1, output, ID2, input);
            } else if (cmd == "disconnect") {
                ID ID1, ID2;
                Port output, input;
                std::cin >> ID1 >> output >> ID2 >> input;
                circuit->disconnect(ID1, output, ID2, input);
            } else if (cmd == "set") {
                ID id;
                Port port;
                bool isInput;
                int state;
                std::cin >> id >> port >> isInput >> state;
                auto g = circuit->find(id);
                if (g != nullptr) {
                    if (isInput)
                        g->setInputState(port, state);
                    else
                        g->setOutputState(port, state);
                }
            } else if (cmd == "update") {
                ID id;
                std::cin >> id;
                auto g = circuit->find(id);
                if (g != nullptr)
                    g->update();
            } else if (cmd == "click") {
                ID id;
                std::cin >> id;
                auto g = circuit->find(id);
                if (g != nullptr)
                    g->clickAction();
            } else if (cmd == "reset") {
                ID id;
                std::cin >> id;
                auto g = circuit->find(id);
                if (g != nullptr)
                    g->reset();
            } else if (cmd == "clear") {
                ID id;
                std::cin >> id;
                auto g = circuit->find(id);
                if (g != nullptr)
                    g->clear();
            } else if (cmd == "propagate") {
                ID id;
                std::cin >> id;
                auto gates = circuit->find(id);
                Engine::getInstance().propagateSignal(circuit, gates);
            } else if (cmd == "restart") {
                Engine::getInstance().restart(circuit);
            } else if (cmd == "calculate") {
                Engine::getInstance().calcLogicImmediate(circuit);
            } else if (cmd == "changeClock") {
                ID id;
                Tick onperiod, offperiod, phase;
                std::cin >> id >> onperiod >> offperiod >> phase;
                auto g = circuit->find(id);
                if (g->getGateType() != CLOCK) continue;
                auto g1 = std::static_pointer_cast<Clock, Gate>(g);
                g1->changeSettings(onperiod, offperiod, phase);
            } else if (cmd == "changeDelay") {
                ID id;
                Tick phase;
                std::cin >> id >> phase;
                auto g = circuit->find(id);
                if (g->getGateType() != DELAY) continue;
                auto g1 = std::static_pointer_cast<Delay, Gate>(g);
                g1->setDelay(phase);
            }
        }
    }

    bool App::closeShell() {
        Logicon::Logger::info("Shell closed");
        return true;
    }

//-----------------------------------------------------------------------------
// GUI
//-----------------------------------------------------------------------------

    bool App::initGui() {
        Logicon::Logger::info("MODE:   GUI");
        tickrate = 10;
        state = STATE::PAUSED;

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
        if (!MenuWidget::getInstance().init() ||
            !BlocksWidget::getInstance().init() ||
            !CanvasWidget::getInstance().init(circuit) ||
            !FooterWidget::getInstance().init())
            return false;

        timer = 0;
        simulationSpeed = ImGui::GetTime();
        return true;
    }

    void App::runGUI() {
        // Main app loop
        while (!glfwWindowShouldClose(this->window)) {
            glfwPollEvents();
            ImGui_ImplGlfwGL3_NewFrame();

            // if (tickrate...) engine.calcLogic(this.canvasWidget.gCircuit.circuit)
            switch (state) {

                case RUNNING:
                    FooterWidget::getInstance().pushStatus(std::to_string(fromMilis(
                        ImGui::GetTime() - simulationSpeed)));
                    if (timer >= tickrate) {
                        Engine::getInstance().calc(circuit, false);
                        timer -= tickrate;
                        simulationSpeed = ImGui::GetTime();
                    }
                    break;
                case PAUSED:
                    if (STEP_NEXT_STEP) {
                        Engine::getInstance().calcLogic(circuit);
                        STEP_NEXT_STEP = false;
                    }
                    break;
                case RESTART:
                    circuit->INITIALIZED_FLAG = false;
                    timer = 0;
                    state = PAUSED;
                    break;
            }
            this->render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui::Render();

            glfwSwapBuffers(window);
            timer++; // next loop
        }
    }

    void App::render() {
        int canvas_w, canvas_h;
        glfwGetFramebufferSize(window, &canvas_w, &canvas_h);

        UI::Vec2 canvas_pos = {UI::MARGIN,
                               UI::MARGIN + UI::MENU_WIDGET_HEIGHT + UI::MARGIN};

        UI::Vec2 canvas_size = {canvas_w - UI::MARGIN - UI::MARGIN - UI::BLOCKS_WIDGET_WIDTH - UI::MARGIN,
                                canvas_h - UI::MARGIN - UI::MENU_WIDGET_HEIGHT - UI::MARGIN - UI::MARGIN -
                                    UI::FOOTER_WIDGET_HEIGHT};

        // Menu Widget
        MenuWidget::getInstance().render({UI::MARGIN,
                                          UI::MARGIN},
                                         {canvas_w - 2 * UI::MARGIN - UI::BLOCKS_WIDGET_WIDTH - UI::MARGIN,
                                          UI::MENU_WIDGET_HEIGHT},
                                         canvas_pos,
                                         canvas_size);
        // Blocks Widget
        BlocksWidget::getInstance().render({canvas_w - UI::MARGIN - UI::BLOCKS_WIDGET_WIDTH,
                                            UI::MARGIN},
                                           {UI::BLOCKS_WIDGET_WIDTH,
                                            canvas_h - (UI::MARGIN + UI::FOOTER_WIDGET_HEIGHT + UI::MARGIN)});

        // Canvas Widget
        CanvasWidget::getInstance().render(canvas_pos, canvas_size);

        // Footer Widget
        FooterWidget::getInstance().render({0,
                                            (float) canvas_h - (UI::FOOTER_WIDGET_HEIGHT)},
                                           {(float) canvas_w,
                                            UI::FOOTER_WIDGET_HEIGHT});

        // Trigger postponed removal of gates
        ID postponedRemoval = CanvasWidget::getInstance().getGCircuit()->postponedRemoval;
        if (postponedRemoval != -1) {
            CanvasWidget::getInstance().getGCircuit()->remove(postponedRemoval);
            CanvasWidget::getInstance().getGCircuit()->getCircuit()->remove(postponedRemoval);
            Engine::getInstance().calcTree(CanvasWidget::getInstance().getGCircuit()->getCircuit());
            CanvasWidget::getInstance().getGCircuit()->postponedRemoval = -1;
        }
    }

    bool App::closeGui() {
        if (MenuWidget::getInstance().close() ||
            !BlocksWidget::getInstance().close() ||
            !CanvasWidget::getInstance().close() ||
            !FooterWidget::getInstance().close())
            return false;


        ImGui_ImplGlfwGL3_Shutdown();
        glfwTerminate();

        return true;
    }

} // namespace Logicon