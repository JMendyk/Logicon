//
// Created by rufus on 07.01.18.
//

#include "assetLoader.h"

namespace Logicon {

    AssetLoader *AssetLoader::instance = nullptr;


    Texture &AssetLoader::gate_and() {
        return instance->_gate_and;
    }

    Texture &AssetLoader::gate_clock() {
        return instance->_gate_clock;
    }

    Texture &AssetLoader::gate_delay() {
        return instance->_gate_delay;
    }

    Texture &AssetLoader::gate_input_high() {
        return instance->_gate_input_high;
    }

    Texture &AssetLoader::gate_input_low() {
        return instance->_gate_input_low;
    }

    Texture &AssetLoader::gate_nand() {
        return instance->_gate_nand;
    }

    Texture &AssetLoader::gate_nor() {
        return instance->_gate_nor;
    }

    Texture &AssetLoader::gate_not() {
        return instance->_gate_not;
    }

    Texture &AssetLoader::gate_or() {
        return instance->_gate_or;
    }

    Texture &AssetLoader::gate_switch_off() {
        return instance->_gate_switch_off;
    }

    Texture &AssetLoader::gate_switch_on() {
        return instance->_gate_switch_on;
    }

    Texture &AssetLoader::gate_xnor() {
        return instance->_gate_xnor;
    }

    Texture &AssetLoader::gate_xor() {
        return instance->_gate_xor;
    }

    Texture &AssetLoader::icon_new() {
        return instance->_icon_new;
    }

    Texture &AssetLoader::icon_open() {
        return instance->_icon_open;
    }

    Texture &AssetLoader::icon_pause() {
        return instance->_icon_pause;
    }

    Texture &AssetLoader::icon_play() {
        return instance->_icon_play;
    }

    Texture &AssetLoader::icon_restart() {
        return instance->_icon_restart;
    }

    Texture &AssetLoader::icon_save() {
        return instance->_icon_save;
    }

    Texture &AssetLoader::icon_step() {
        return instance->_icon_step;
    }

    void AssetLoader::_loadAssets() {
        _gate_and = load_texture("assets/gates/gate_and.png");
        _gate_clock = load_texture("assets/gates/gate_clock.png");
        _gate_delay = load_texture("assets/gates/gate_delay.png");
        _gate_input_high = load_texture("assets/gates/gate_input_high.png");
        _gate_input_low = load_texture("assets/gates/gate_input_low.png");
        _gate_nand = load_texture("assets/gates/gate_nand.png");
        _gate_nor = load_texture("assets/gates/gate_nor.png");
        _gate_not = load_texture("assets/gates/gate_not.png");
        _gate_or = load_texture("assets/gates/gate_or.png");
        _gate_switch_off = load_texture("assets/gates/gate_switch_off.png");
        _gate_switch_on = load_texture("assets/gates/gate_switch_on.png");
        _gate_xnor = load_texture("assets/gates/gate_xnor.png");
        _gate_xor = load_texture("assets/gates/gate_xor.png");
        _icon_new = load_texture("assets/icons/icon_new.png");
        _icon_open = load_texture("assets/icons/icon_open.png");
        _icon_pause = load_texture("assets/icons/icon_pause.png");
        _icon_play = load_texture("assets/icons/icon_play.png");
        _icon_restart = load_texture("assets/icons/icon_restart.png");
        _icon_save = load_texture("assets/icons/icon_save.png");
        _icon_step = load_texture("assets/icons/icon_step.png");
    }

    AssetLoader *AssetLoader::assetLoader() {
        if (instance == nullptr) {
            instance = new AssetLoader();
        }
        return instance;
    }

    void AssetLoader::loadAssets() {
        assetLoader();
        instance->_loadAssets();
    }
} // namespace Logicon


