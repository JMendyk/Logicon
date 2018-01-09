//
// Created by rufus on 12.12.17.
//

#ifndef LOGICON_ENGINE_H
#define LOGICON_ENGINE_H

#include "circuit.h"

namespace Logicon {
    /**
     * @brief Engine calculates next state of whole circuit.
     *
     * Engine allows user to initialize the first state of a circuit and calculate next states based on current.
     */
    class Engine{

    private:

        ///LOCAL VARIABLES
        std::list<std::shared_ptr<Gate> > graph;
        int i;
        ID id;
        std::map<ID, int> m;
        std::vector<Connection> con;
        Connection co;
        ///===========================

        ///Order of updating the gates
        std::vector<ID> q;

    public:
        /**
         * Initializes new circut.
         * Sets its state on tick 0.
         */
        void restart(Circuit c);

        /**
         * Calculates order of updating WITHOUT setting states of any gates.
         * Used when downloading previously used circut.
         */
        void calcTree(Circuit c);

        /**
         * Calculates state of circut based on the previous one.
         */
        void calcLogic(Circuit c);
    };
} // namespace Logicon

#endif //LOGICON_ENGINE_H
