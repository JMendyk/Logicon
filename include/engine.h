//
// Created by inverb on 10.01.18.
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
    class Engine {
//-----------------------------------------------------------------------------
    private:
        Engine();

    public:
        static Engine &getInstance();

        Engine(const Engine &) = delete;

        void operator=(const Engine &) = delete;
//-----------------------------------------------------------------------------
    private:

        /// LOCAL VARIABLES
        std::list<std::shared_ptr<Gate> > graph;
        int i;
        std::map<ID, int> m;
        std::vector<Connection> con;
        ///===========================

        /// Order of updating the gates
        std::vector<ID> q;

    public:

        /**
         * Updates inputs of gates connected with gate gate.
         *
         */
        void propagateSignal(std::shared_ptr<Circuit> c, std::shared_ptr<Gate> gate);

        /**
         * Initializes new circut.
         * Sets its state on tick 0.
         */
        void restart(std::shared_ptr<Circuit> c);

        /**
         * Calculates order of updating WITHOUT setting states of any gates.
         * Used when downloading previously used circut.
         */
        void calcTree(std::shared_ptr<Circuit> c);

        /**
         * Calculates state of circuit based on the previous one.
         * Calculates all gates at once and then pushes results through edges.
         */
        void calcLogic(std::shared_ptr<Circuit> c);

        /**
         * Calculates state of circuit based on the previous one.
         * Calculates state of each gate and immediately pushes it's results.
         * (Should be better option for gui)
         */
        void calcLogicImmediate(std::shared_ptr<Circuit> c);

        /**
         * Calculates next state of circuit with deduction based on INITIALISED_FLAG
         *
         */
        void calc(std::shared_ptr<Circuit> c, bool immediate);
    };
} // namespace Logicon

#endif //LOGICON_ENGINE_H
