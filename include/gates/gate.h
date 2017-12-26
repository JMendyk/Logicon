//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_GATE_H
#define LOGICON_GATE_H

#include <types.h>


namespace Logicon {

    /**
     * @brief Abstract class representing a logic gate.
     *
     * All other gates should be derived from this class.
     * Each derived class has to implement it's own constructor that prior to anything runs constructor in Gate.
     * Each derived class has to initialize inputs[] and outputs[] in constructor.
     */
    class Gate {

    private:
        /// LOCAL TYPEDEFS
        /// ==============

        /// iterable container of outgoing connections from certain port
        typedef std::vector<Connection> PortConnectionList_;

        /// MEMBERS
        /// =======

        /// ID representing gate
        const ID id;
        /// ordered container of all inputs the gate has as tuples <state, container of input collections>
        std::vector<std::pair<State, PortConnectionList_> > inputs;
        /// ordered container of all outputs the gat has as tuples <states, containerOfConnections>
        std::vector<std::pair<State, PortConnectionList_> > outputs;
        /// additional data individual for each gate like labels etc.

    public:
        /**
         * @brief Constructor accepting new unique ID and a number of inputs and outputs.
         * @param ID unique ID identifying block
         * @param inputsCount number of inputs
         * @param outputsCount number of outputs
         */
        explicit Gate(ID id, unsigned int inputsCount, unsigned int outputsCount);

        // ======
        // INPUTS
        // ======

        /**
         * @brief Returns this gate's ID.
         *
         * @return ID of this gate
         */
        ID getID() const;

        /**
        * @brief Returns inputs count.
        * @return number of inputs
        */
        int getInputsCount() const;

        /**
        * @brief Returns state of specified input.
        *
        * @param input input port of this gate
        * @return State representing state of given input
        */
        State getInputState(Port input) const;

        /**
        * @brief Changes state of specified input.
        *
        * @warning In the future release may change to addInput if multiple
         * input connections will be supported.
         *
        * @param input input port of this gate
        * @param state new state for given input
        */
        void setInputState(Port input, State state);

        /**
         * @brief Check if specified port is connected with anything.
         * @param input input port of this gate
         * @return true if given port is not connected with anything, false otherwise
         */
        bool isInputEmpty(Port input) const;

        /**
        * @brief Checks if given input is connected with given gate at given port.
        *
        * @param input input port of this gate
        * @param otherId ID of the connected gate
        * @param otherPort output port of the connected gate
        * @return true if connection otherId:otherPort -> this:index exists, false otherwise
        */
        bool isInputConnectedWith(Port input, ID otherId, Port otherPort);

        /**
        * @brief Returns list of connections with given input.
        *
        * @warning Currently only a single connection at given input exists,
         * so the returned list has at most one element in it. Returning list
         * instead of single Connection shifts the responsibility of checking
         * for connection existence onto the caller. Returning list is also a way
         * to adapt for possible future change in API where multiple connections
         * may be linked to one input port.
        *
        * @param input input port of this gate
        * @return iterable container of connections on given input port
        */
        PortConnectionList_ getInputConnections(Port input) const;

        /**
        * @brief Changes information about connection at specified input.
        *
        * @warning It won't check if connection is valid, it will just set the fields!
        *
        * @param input input port of this gate
        * @param otherId ID of the connected gate
        * @param otherPort input port of the connected gate
        */
        void setInputConnection(Port input, ID otherId, Port otherPort);

        /**
         * @brief Removes all connections from given input port
         * @param input input port of this gate
         */
        void clearInputConnections(Port input);

        // =======
        // OUTPUTS
        // =======

        /**
* @brief Returns outputs count.
* @return number of outputs
*/
        int getOutputsCount() const;

        /**
        * @brief Returns state of specified output.
        *
        * @param output output port of this gate
        * @return State representing state of given output
        */
        State getOutputState(Port output) const;

        /**
        * @brief Changes state of specified output.
        *
        * @param output output port of this gate
        * @param state new state to be set on given output
        */
        void setOutputState(Port output, State state);

        /**
         * @brief Check if specified port is connected with anything.
         * @param output output port of this gate
         * @return true if given port is not connected with anything, false otherwise
         */
        bool isOutputEmpty(Port output) const;

        /**
        * @brief Checks if given output is connected with given gate at given port.
        *
        * @param output output port of this gate
        * @param otherId ID of the connected gate
        * @param otherPort input port of the connected gate
        * @return true if connection this:index -> otherId:otherPort exists, false otherwise
        */
        bool isOutputConnectedWith(Port output, ID otherId, Port otherPort) const;

        /**
        * @brief Returns list of all connections at specified port.
        *
        * @note Multiple connections outgoing from single port can exist.
        *
        * @param output output port of this gate
        * @return iterable container of connections at given output port
        */
        PortConnectionList_ getOutputConnections(Port output);

        /**
        * @brief Adds another output connection at given output port.
        * @note If connection exists, operation is cancelled.
        *
        * @warning It won't check if connection is valid, it will just set the fields!
        *
        * @param output output port of this gate
        * @param otherId ID of the connected gate
        * @param otherPort input port of the connected gate
        */
        void addOutputConnection(Port output, ID otherId, Port otherPort);

        /**
        * @brief Finds and removes specified connection from given output port.
        *
        * @note If connection doesn't exist, nothing happens.
        *
        * @param output output port of this gate
        * @param otherId ID of the connected gate
        * @param otherPort input port of the connected gate
        */
        void removeOutputConnection(Port output, ID otherId, Port otherPort);

        /**
         * @brief Removes all connections from given output
         */
        void clearOutputConnections(Port output);

        /**
         * @brief Calculates states of outputs according to block's logic.
         */
        virtual void update()=0;

        /**
         * @brief Defines behavior of gate when the gate is `clicked`.
         */
        virtual void clickAction() {};
    };
} // namespace Logicon

#endif //LOGICON_GATE_H
