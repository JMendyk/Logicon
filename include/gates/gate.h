//
// Created by rufus on 11.12.17.
//

#ifndef LOGICON_GATE_H
#define LOGICON_GATE_H

#include <string>
#include <vector>
#include <circuit.h>
#include <types.h>
#include "data.h"


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
        typedef std::vector<Connection> PortConnectionsList_;

        /// reference to parent TODO: change to shared_pointer
        const Circuit parent;
        /// ID representing gate
        ID id;
        /// ordered container of all inputs the gate has as tuples <state, connectedBlockId, connectedBlockPortIndex>
        std::vector<std::tuple<PortState, ID, Port> > inputs; //
        /// ordered container of all outputs the gat has as tuples <states, containerOfConnections>
        std::vector<std::pair<PortState, PortConnectionsList_> > outputs;
        /// additional data individual for each gate like labels etc.

    public:
        /**
         * @brief Constructor acceping new uniqe ID and a reference to parent circuit.
         * @param ID uniqe ID identifying block
         * @param circuit reference to parent circuit
         */
        explicit Gate(ID id, Circuit parent);

        /**
         * @brief Returns this gate's ID.
         *
         * @return ID of this gate
         */
        ID getID() const;

        /**
         * @brief Calculates states of outputs according to block's logics.
         */
        virtual void update()=0;

        /**
         * @brief Defines behavior of gate when the gate is `clicked`.
         */
        virtual void clickAction() {};

        /**
         * @brief Returns state of specified input.
         *
         * @param index index of input which state we want
         * @return PortState_ representing state of given input
         */
        PortState getInputState(Port index);

        /**
         * @brief Changes state of specified input.
         *
         * @param index index of input which state we want to change
         * @param state new state for given input
         */
        void setInputState(Port index, PortState state);

        /**
         * @brief Returns pair describing witch which element specified input is connected to.
         *
         * Only one one connection at given input exists.
         *
         * @param index index of input which info we want
         * @return pair <ID, PortIndex> identifying other end of connection
         */
        Connection getInputConnection(Port index);

        /**
         * @brief Changes information about connection at specified input.
         *
         * @warning It won't check if connection is valid, it will just set the fields!
         *
         * @param index index of input which info we want to change
         * @param otherId ID of block we connect to
         * @param otherPort index of block's port we connect to
         */
        void setInputConnection(Port index, ID otherId, Port otherPort);

        /**
         * @brief Returns state of specified output.
         *
         * @param index index of output which state we want
         * @return PortState_ representing state of given output
         */
        PortState getOutputState(Port index);

        /**
         * @brief Changes state of specified output.
         *
         * @param index index of output which state we want to change
         * @param state new state for given output
         */
        void setOutputState(Port index, PortState state);

        /**
         * @brief Adds another output connection at given output port.
         * If connection exists, operation is cancelled.
         *
         * @warning It won't check if connection is valid, it will just set the fields!
         *
         * @param index index of output to which new connection should be added
         * @param other_id ID of block we connect to
         * @param other_port index of block's port we connect to
         */
        void addOutputConnection(Port index, ID other_id, Port other_port);

        /**
         * @brief Finds and removes given connection from specified output.
         *
         * If connection doesn't exist, operation is cancelled.
         *
         * @param index index of output from which we want to remove connection
         * @param other_id ID of block we are currently connected and want to disconnect
         * @param other_port index of connected block's port we are currently connected and want to disconnect
         */
        void removeOutputConnection(Port index, ID other_id, Port other_port);

        /**
         * @brief Returns list of all connections at specified port.
         *
         * Multiple connections outgoing from single port can exist.
         *
         * @param index index of output which connections list we want
         * @return container with connections outgoing from given output
         */
        PortConnectionsList_ getOutputConnections(Port index);

    };
} // namespace Logicon

#endif //LOGICON_GATE_H
