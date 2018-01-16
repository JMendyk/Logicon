//
// Created by JMendyk on 28.12.17.
//

#ifndef LOGICON_G_CIRCUIT_H
#define LOGICON_G_CIRCUIT_H

#include "types.h"
#include "gui/gUtils.h"
#include "gBlock.h"

#include <set>
#include <map>
#include <memory>
#include <circuit.h>

namespace Logicon {

    /**
     * @remarks Currently some of the methods return ID, which required defining special "NOT FOUND" value of ID.
     * Maybe methods should be reconsidered and return pointers.
     */
    class GCircuit : public std::enable_shared_from_this<GCircuit> {

        // local typedef for container
        typedef std::list<std::shared_ptr<GBlock>> _GBLOCK_CONTAINER_TYPE;

        std::shared_ptr<Circuit> circuit;               /// Model it represents
        _GBLOCK_CONTAINER_TYPE gBlocks;                 /// list with positions and blocks, TODO: spatial data struct

    public:
        // @formatter:off
        int         POSTPONED_OPERATIONS;           // Flag holding postponed operations to execute
        const int   POSTPONED_REMOVE      = 1 << 0;
        const int   POSTPONED_CLEAR       = 1 << 1;
        const int   POSTPONED_CONNECT     = 1 << 2;
        const int   POSTPONED_DISCONNECT  = 1 << 3;
        ID          postponedRemoveId;                  /// ID of gate to be removed, -1 if no postponed removal
        Connection  postponedConnectFrom;               /// Connection info for postponed connect operation...
        Connection  postponedConnectTo;                 /// ...
        Connection  postponedDisconnectFrom;            /// Connection info for postponed disconnect operation...
        Connection  postponedDisconnectTo;              /// ...
        // @formatter:on
        GCircuit(std::shared_ptr<Circuit> circuit);

        /**
         * Initialize GCircuit
         * @return
         */
        bool init();

        /**
         * @brief Run while app closes or opens new file
         *
         * @return true if close was successful
         */
        bool close();

        /**
         * @brief Returns this circuit
         *
         * @return this
         */
        const std::shared_ptr<Circuit> getCircuit() const;

        /**
         * @brief Returns container holding gBlocks
         * @return
         */
        const _GBLOCK_CONTAINER_TYPE &getGBlocks() const;

        /**
         * @breif Returns pointer to GBlock at given position
         *
         * @param pos position to check for
         * @return pointer to GBlock or nullptr if block at given pos doesn't exist
         */
        std::shared_ptr<GBlock> getGBlockAt(UI::Vec2 &pos);

        /**
         * @breif Returns pointer to GBlock by ID
         *
         * @param id GBlock's ID
         * @return GBlock pointer
         */
        std::shared_ptr<GBlock> getGBlockByID(ID id);

        /**
         * @brief Inserts given gate at given position.
         * @warning operation is postponed for the end of render() loop. Main logics in posponeXXX()
         *
         * @details Creates new GBlock based on gate at given position.
         * @warning Doesn't check if the place is occupied!
         * @param gate gate to be inserted
         * @param pos position to where put a gate
         */
        void insert(std::shared_ptr<Gate> gate, UI::Vec2 pos);

        /**
         * @brief Removes GBlock from visual model and backed model
         * @warning operation is postponed for the end of render() loop. Main logics in posponeXXX()
         *
         * @param id ID of GBlock that should be removed
         */
        void remove(ID id);

        /**
         * @brief clears GCircuit and model
         * @warning operation is postponed for the end of render() loop. Main logics in posponeXXX()
         */
        void clear();

        /**
         * @brief Connects gates with specified IDs on specified ports
         * @warning operation is postponed for the end of render() loop. Main logics in posponeXXX()
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
         * @warning operation is postponed for the end of render() loop. Main logics in posponeXXX()
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
         * @breif Checks if in the rectangle all cells are either free or belong to GBlock
         * @warning operation is postponed for the end of render() loop. Main logics in posponeXXX()
         *
         * @param id ID of GBlock
         * @param rect Rectangle to check
         * @return false if all cells are either free or belong to GBlock
         */
        bool isOccupied(ID id, UI::Rect rect);

        /**
         * @brief Moves existing GBlock to new position
         *
         * @param id ID of GBlock that should be moved
         * @param pos new position as vector of integer values
         * @return true if move operation was successful
         */
        bool move(ID id, UI::Vec2 pos);

        /**
         * @brief Renders GCircuit
         * @param window_pos
         * @param window_size
         */
        void render(const UI::Vec2 &window_pos, const UI::Vec2 &window_size);

//-----------------------------------------------------------------------------
// INTERNAL
//-----------------------------------------------------------------------------
    private:

        // TODO: move responsibility to Canvas widget
        /// @brief scrolls canvas
        void scrollCanvas();

        /**
         * @brief Executes postponed operations. Executed after render to not interrupt rendering loops
         */
        void executePostponed();

        /// @brief apllies modification during executePostponed()
        void postponedRemove(ID id);

        /// @brief apllies modification during executePostponed()
        void postponedClear();

        /// @brief apllies modification during executePostponed()
        void postponedConnect(ID idFrom, Port output, ID idTo, Port input);

        /// @brief apllies modification during executePostponed()
        void postponedDisconnect(ID idFrom, Port output, ID idTo, Port input);
    };

} // namespace Logicon

#endif //LOGICON_G_CIRCUIT_H
