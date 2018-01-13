//
// Created by rufus on 07.01.18.
//

#ifndef LOGICON_ASSETLOADER_H
#define LOGICON_ASSETLOADER_H

#include <graphics.h>
#include "types.h"

namespace Logicon {

    class AssetLoader {
    private:

        Texture _gate_and;
        Texture _gate_clock;
        Texture _gate_delay;
        Texture _gate_input_on;
        Texture _gate_input_off;
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

//-----------------------------------------------------------------------------
    private:
        AssetLoader() = default;

    public:
        static AssetLoader &getInstance();

        AssetLoader(const AssetLoader &) = delete;

        void operator=(const AssetLoader &) = delete;
//-----------------------------------------------------------------------------

    public:

        enum ICON {
            NEW, OPEN, PAUSE, PLAY, RESTART, SAVE, STEP
        };

        static void loadAssets();

        static Texture &getGateTexture(GATE_TYPE gate);

        static Texture &getIconTexture(ICON icon);

    };
} // namespace Logicon

#endif //LOGICON_ASSETLOADER_H
