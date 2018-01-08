//
// Created by Tooster on 16.12.2017.
//

#ifndef LOGICON_CIRCUIT_H
#define LOGICON_CIRCUIT_H

#include "types.h"
#include <gates/gate.h>


namespace Logicon {
    /**
     * @brief Circuit represents collection of gates and connections between them.
     *
     * Circuit is in fact a graph with gates as it's nodes. It allows to perform various actions on the model such as:
     * connecting and disconnecting gates, adding new gates, removing gates and finding gates by ID.
     */
    class Circuit {
    private:
        const ID id;
        std::map<ID, std::shared_ptr<Gate>> gates;

    public:
        Data data;                                      /// public access data
        bool INITIALIZED_FLAG;                          /// true if circuit was calculated for the first time, false otherwise.
        /**
         * @brief Generates next unique ID in range [0, MAX_UINT] for elements
         * @return new uniqe ID
         */
        static Logicon::ID nextID();

        /// Constructor
        explicit Circuit(ID id);

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
         * @note If connection doesn't exist, nothing happens.
         *
         * @param idFrom gate from which the wire exits (gate A in connection A->B)
         * @param output output port in the first gate (output port of gate A in connection A->B)
         * @param idTo gate where the wire enters (gate B in connection A->B)
         * @param input input port in the second gate (input port of gate B in connection A->B)
         */
        void disconnect(ID idFrom, Port output, ID idTo, Port input);

        /**
         * @brief Adds new gate to the circuit.
         *
         * @details Should accept a shared pointer to the object created using std::make_shared
         *
         * @param gate shared pointer to the newly created Gate object
         */
        void add(std::shared_ptr<Gate> gate);

        /**
         * @brief Removes gate with specified ID from the circuit.
         *
         * If the gate is not in the circuit, nothing happens.
         * @param id id of a gate to remove from the circuit.
         */
        void remove(ID id);

        /**
         * @deprecated
         * @brief Returns share pointer to gate object from the circuit based on the ID
         * @return existing shared pointer to found gate or nullptr if gate with given ID is not found
         */
        std::shared_ptr<Gate> find(const ID &id) const;

        /**
         * @brief Returns share pointer to gate object from the circuit based on the ID
         * @note same as find, changed name to more intuitive
         * @return existing shared pointer to found gate or nullptr if gate with given ID is not found
         */
        std::shared_ptr<Gate> getGateById(ID id) const;

        /**
         * @brief Returns iterable list of shared pointers to gates associated with circuit
         * @return iterable container of pointers to gates.
         */
        std::list<std::shared_ptr<Gate>> getGates();

        /**
         * @brief Clears circuit deleting all gates
         */
        void clear();

    };
} // namespace Logicon

#endif //LOGICON_CIRCUIT_H
