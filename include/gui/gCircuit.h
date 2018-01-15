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
        ID postponedRemoval;                           /// ID of gate to be removed

        GCircuit(std::shared_ptr<Circuit> circuit);

/**
         * Initialize GCircuit
         * @return
         */
        bool init();

        /**
         * @brief Run while app closes or opens new file
         * @return true if close was successful
         */
        bool close();

        /**
         * @brief Returns this circuit
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
         * @param pos position to check for
         * @return pointer to GBlock or nullptr if block at given pos doesn't exist
         */
        std::shared_ptr<GBlock> getGBlockAt(UI::Vec2 &pos);

        /**
         * @breif Returns pointer to GBlock by ID
         * @param id GBlock's ID
         * @return GBlock pointer
         */
        std::shared_ptr<GBlock> getGBlockByID(ID id);

        /**
         * @brief Inserts given gate at given position.
         * @details Creates new GBlock based on gate at given position.
         * @warning Doesn't check if the place is occupied!
         * @param gate gate to be inserted
         * @param pos position to where put a gate
         */
        void insert(std::shared_ptr<Gate> gate, UI::Vec2 pos);

        /**
         * @brief Removes GBlock from visual model
         * @param id ID of GBlock that should be removed
         */
        void remove(ID id);

        /**
         * @brief clears GCircuit
         */
        void clear();

        /**
         * @breif Checks if in the rectangle all cells are either free or belong to GBlock
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

    private:

        // TODO: move responsibility to Canvas widget
        void scrollCanvas();
    };

} // namespace Logicon

#endif //LOGICON_G_CIRCUIT_H
