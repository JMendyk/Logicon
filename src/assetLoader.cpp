//
// Created by rufus on 07.01.18.
//

#include "assetLoader.h"

namespace Logicon {


    AssetLoader &AssetLoader::getInstance() {
        static AssetLoader instance;
        return instance;
    }

    void AssetLoader::loadAssets() {
        getInstance()._gate_and = load_texture("assets/gates/gate_and.png");
        getInstance()._gate_clock = load_texture("assets/gates/gate_clock.png");
        getInstance()._gate_delay = load_texture("assets/gates/gate_delay.png");
        getInstance()._gate_input_on = load_texture("assets/gates/gate_input_high.png");
        getInstance()._gate_input_off = load_texture("assets/gates/gate_input_low.png");
        getInstance()._gate_nand = load_texture("assets/gates/gate_nand.png");
        getInstance()._gate_nor = load_texture("assets/gates/gate_nor.png");
        getInstance()._gate_not = load_texture("assets/gates/gate_not.png");
        getInstance()._gate_or = load_texture("assets/gates/gate_or.png");
        getInstance()._gate_switch_on = load_texture("assets/gates/gate_switch_on.png");
        getInstance()._gate_switch_off = load_texture("assets/gates/gate_switch_off.png");
        getInstance()._gate_xnor = load_texture("assets/gates/gate_xnor.png");
        getInstance()._gate_xor = load_texture("assets/gates/gate_xor.png");
        getInstance()._icon_new = load_texture("assets/icons/icon_new.png");
        getInstance()._icon_open = load_texture("assets/icons/icon_open.png");
        getInstance()._icon_pause = load_texture("assets/icons/icon_pause.png");
        getInstance()._icon_play = load_texture("assets/icons/icon_play.png");
        getInstance()._icon_restart = load_texture("assets/icons/icon_restart.png");
        getInstance()._icon_save = load_texture("assets/icons/icon_save.png");
        getInstance()._icon_step = load_texture("assets/icons/icon_step.png");
    }

    Texture &AssetLoader::getGateTexture(GATE_TYPE gate) {
        switch (gate) {
            case Logicon::NOT:
                return getInstance()._gate_not;
            case Logicon::DELAY:
                return getInstance()._gate_delay;
            case Logicon::SWITCH_ON:
                return getInstance()._gate_switch_on;
            case Logicon::SWITCH_OFF:
                return getInstance()._gate_switch_off;
            case Logicon::AND:
                return getInstance()._gate_and;
            case Logicon::OR:
                return getInstance()._gate_or;
            case Logicon::XOR:
                return getInstance()._gate_xor;
            case Logicon::NAND:
                return getInstance()._gate_nand;
            case Logicon::NOR:
                return getInstance()._gate_nor;
            case Logicon::XNOR:
                return getInstance()._gate_xnor;
            case Logicon::CLOCK:
                return getInstance()._gate_clock;
            case Logicon::INPUT_ON:
                return getInstance()._gate_input_on;
            case Logicon::INPUT_OFF:
                return getInstance()._gate_input_off;
        }
    }

    Texture &AssetLoader::getIconTexture(AssetLoader::ICON icon) {
        switch (icon) {
            case NEW:
                return getInstance()._icon_new;
            case OPEN:
                return getInstance()._icon_open;
            case PAUSE:
                return getInstance()._icon_pause;
            case PLAY:
                return getInstance()._icon_play;
            case RESTART:
                return getInstance()._icon_restart;
            case SAVE:
                return getInstance()._icon_save;
            case STEP:
                return getInstance()._icon_step;
        }
    }
} // namespace Logicon


