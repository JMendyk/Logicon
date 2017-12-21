//
// Created by JMendyk on 18.12.17.
//

#include "widgets/menu_widget.h"

namespace Logicon {

    ImFont* myFont = nullptr;

    bool MenuWidget::init(GLFWwindow* window) {
        this->window = window;

        static ImFontConfig imFontConfig = ImFontConfig();
        imFontConfig.SizePixels = 32.0f;
        imFontConfig.RasterizerMultiply = 4;
        myFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("../dependencies/imgui/extra_fonts/Roboto-Medium.ttf", 32.0f, &imFontConfig);

        return true;
    }

    bool MenuWidget::close() {
        return true;
    }

    void MenuWidget::render_ui(const ImVec2 &window_pos, const ImVec2 &window_size) {

    }

};
