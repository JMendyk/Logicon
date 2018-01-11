//
// Created by rufus on 07.01.18.
//

#ifndef LOGICON_ASSETLOADER_H
#define LOGICON_ASSETLOADER_H

#include <graphics.h>

namespace Logicon {

    class AssetLoader {
    private:
        static AssetLoader *instance;
        Texture _gate_and;
        Texture _gate_clock;
        Texture _gate_delay;
        Texture _gate_input_high;
        Texture _gate_input_low;
        Texture _gate_nand;
        Texture _gate_nor;
        Texture _gate_not;
        Texture _gate_or;
        Texture _gate_switch_off;
        Texture _gate_switch_on;
        Texture _gate_xnor;
        Texture _gate_xor;
        Texture _icon_new;
        Texture _icon_open;
        Texture _icon_pause;
        Texture _icon_play;
        Texture _icon_restart;
        Texture _icon_save;
        Texture _icon_step;

        AssetLoader() = default;

        void _loadAssets();

    public:
        static AssetLoader *assetLoader();

        static void loadAssets();

        static Texture &gate_and();

        static Texture &gate_clock();

        static Texture &gate_delay();

        static Texture &gate_input_high();

        static Texture &gate_input_low();

        static Texture &gate_nand();

        static Texture &gate_nor();

        static Texture &gate_not();

        static Texture &gate_or();

        static Texture &gate_switch_off();

        static Texture &gate_switch_on();

        static Texture &gate_xnor();

        static Texture &gate_xor();

        static Texture &icon_new();

        static Texture &icon_open();

        static Texture &icon_pause();

        static Texture &icon_play();

        static Texture &icon_restart();

        static Texture &icon_save();

        static Texture &icon_step();

    };
} // namespace Logicon

#endif //LOGICON_ASSETLOADER_H
