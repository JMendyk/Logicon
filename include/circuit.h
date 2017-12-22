//
// Created by Tooster on 16.12.2017.
//

#ifndef LOGICON_CIRCUIT_H
#define LOGICON_CIRCUIT_H

#include <gates/gate.h>
#include "types.h"
#include <map>
#include <list>

namespace Logicon {
    /**
     * @brief Circuit represents collection of gates and connections between them.
     *
     * Circuit is in fact a graph with gates as it's nodes. It allows to perform various actions on the model such as:
     * connecting and disconnecting gates, adding new gates, removing gates and finding gates by ID.
     */
    class Circuit {
        ID id;
        std::map<ID, Gate> gates;
        Data data;

        /**
         * @brief Connects gates with specified IDs on specified ports
         *
         * If something is connected to the input port, it gets disconnected.
         * @param idFrom gate from which the wire exits (gate A in connection A->B)
         * @param output output port in the first gate (output port of gate A in connection A->B)
         * @param idTo gate where the wire enters (gate B in connection A->B)
         * @param input input port in the second gate (input port of gate B in connection A->B)
         */
        void connect(ID idFrom, Port output, ID idTo, Port input);

        /**
         * @brief Disconnects two specified gates on specified ports
         *
         * If connection doesn't exist, nothing happens.
         * @param idFrom gate from which the wire exits (gate A in connection A->B)
         * @param output output port in the first gate (output port of gate A in connection A->B)
         * @param idTo gate where the wire enters (gate B in connection A->B)
         * @param input input port in the second gate (input port of gate B in connection A->B)
         */
        void disconnect(ID idFrom, Port output, ID idTo, Port input);

        /**
         * @brief Adds new gate to the circuit.
         *
         * @warning The gate shouldn't be connected to any other gate before adding (all ports clear).
         * @param gate gate object to add to the circuit
         */
        void add(Gate gate);

        /**
         * @brief Removes gate with specified ID from the circuit.
         *
         * If the gate is not in the circuit, nothing happens.
         * @param id id of a gate to remove from the circuit.
         */
        void remove(ID id);

        /**
         * @brief Returns gate object from the circuit based on the ID
         * @return Found gate or exception if gate is not found
         * @throws IdNotFoundException if ID is not found
         */
        Gate find(ID id);


        /**
         * @brief Returns iterable list of gates associated with circuit
         * @return iterable container of gates.
         */
        std::list<Gate> getGates();

    };
} // namespace Logicon

#endif //LOGICON_CIRCUIT_H
