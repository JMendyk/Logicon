//
// Created by JMendyk on 28.12.17.
//

#ifndef LOGICON_G_CIRCUIT_H
#define LOGICON_G_CIRCUIT_H

#include "iGCircuit.h"

#include "gui/gHelpers.h"

#include "gBlock.h"

#include <set>
#include <map>
#include <memory>

namespace Logicon {

    /**
     * @remarks Currently some of the methods return ID, which required defining special "NOT FOUND" value of ID.
     * Maybe methods should be reconsidered and return pointers.
     */
    class GCircuit : public IGCircuit {

        // TODO: Add Circuit integration
        // Circuit circuit;

        std::map<ID, std::shared_ptr<GBlock>> blocks;

        std::set<std::pair<Connection, Connection>> connections;

        /**
         * @brief Inserts GBlock at position
         * @param x position's x value
         * @param y position's y value
         * @param gBlock GBlock to be inserted
         */
        void insert(UIVec2 pos, ID id, std::shared_ptr<GBlock> gBlock);

        /**
         * @brief Removes GBlock
         * @param gBlockID ID of GBlock that should be removed
         */
        void remove(ID gBlockID);

        /**
         * @brief Moves existing GBlock to new position
         * @details Returns true if where was free space to fit GBlock
         * @param gBlockID ID of GBlock that should be moves
         * @param pos new position
         * @return true if move operation was successful
         */
        bool move(ID gBlockID, UIVec2 pos);

        /**
         * @brief Connects two GBlocks
         * @param idFrom ID of GBlock where connections starts
         * @param output Output port of the starting GBlock
         * @param idTo ID of GBlock where connections ends
         * @param input Input port of the ending GBlock
         */
        void connect(ID idFrom, Port output, ID idTo, Port input);

        /**
         * @brief Disconnects two GBlocks that were previously connected
         * @param idFrom ID of GBlock where connections starts
         * @param output Output port of the starting GBlock
         * @param idTo ID of GBlock where connections ends
         * @param input Input port of the ending GBlock
         */
        void disconnect(ID idFrom, Port output, ID idTo, Port input);

        /**
         * @breif Checks if in the rectangle all cells are either free or belong to GBlock
         * @param id ID of GBlock
         * @param rect Rectangle to check
         * @return false if all cells are either free or belong to GBlock
         */
        bool isOccupied(ID id, UIRect rect);

        /**
         * @breif Returns ID of GBlock that is present in position
         * @param x position's x value
         * @param y position's y value
         * @return ID of GBlock that is present in position
         */
        ID getGBlockIDAt(UIVec2 pos);

        /**
         * @breif Returns GBlock by ID
         * @param gBlockID GBlock's ID
         * @return GBlock
         */
        std::shared_ptr<GBlock> getGBlockByID(ID gBlockID);

        /**
         * @brief Returns pair of GBlock's ID and it's Port that is present in position
         * @param pos position
         * @return pair of GBlock's ID and it's Port that is present in position
         */
        std::pair<ID, Port> getPortAt(UIVec2 pos);


      public:

        bool init();
        void render_ui(const UIVec2 &window_pos, const UIVec2 &window_size);
        bool close();
        bool i_move(ID id, UIVec2 pos) override;
        bool i_isOccupied(ID id, UIRect rect) override;
    };

} // namespace Logicon

#endif //LOGICON_G_CIRCUIT_H
