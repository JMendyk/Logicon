//
// Created by rufus on 12.12.17.
//

#ifndef LOGICON_APP_H
#define LOGICON_APP_H


#include "gates/clock.h"

namespace Logicon {
    /**
     * @brief Main app class.
     * It coordinates work between various components: menus, engine, canvas, circuit, parsers, data etc.
     * Main program loop is located in here.
     */
    class App {
    public:
        void run();
    };
} // namespace Logicon


#endif //LOGICON_APP_H
