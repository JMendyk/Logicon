//
// Created by JMendyk on 29.12.17.
//

#ifndef LOGICON_G_BLOCK_H
#define LOGICON_G_BLOCK_H

#include <graphics.h>
#include "types.h"
#include "gui/gUtils.h"

#include "gPort.h"
#include "gates/gate.h"

namespace Logicon {

    class GCircuit;

    // Enable making shared_ptr from *this pointer
    class GBlock {

        std::weak_ptr<GCircuit> parentCircuit;                  /// Parent GCircuit
        std::shared_ptr<Gate> gate;                             /// Pointer to gate it represents

        UI::Vec2 position;                                      /// position in parent GCircuit in grid coordinates
        UI::Vec2 dimension;                                     /// Vector representing size of gBLock in grid coordinates
        Texture texture;                                        /// Current texture may change in input and switch

        std::vector<std::shared_ptr<GPort>> gInputs;            /// inputs
        std::vector<std::shared_ptr<GPort>> gOutptus;           /// outputs

        bool DRAGGING_FLAG;                                     /// flag saying the block is dragged
        UI::Vec2 dragDeltaExact;                                /// drag delta in canvas coordinates
    public:

        /**
         * @brief Constructor for new GBlock
         * @param parentCircuit parent circuit it belongs to
         * @param gate original Gate from model
         * @param relativePosition in grid coordinates on canvas
         */
        GBlock(std::shared_ptr<GCircuit> parentCircuit, std::shared_ptr<Gate> gate, UI::Vec2 relativePosition);

        /**
         * @brief Renders the gBlock also checking if it is dragged
         * @param should_interact suggestion whether GBlock should respond to user interactions
         */
        void render(bool should_interact);

        const std::shared_ptr<Gate> &getGate() const;

        const UI::Vec2 &getPosition() const;

        const UI::Vec2 &getDimension() const;

        /**
         * @brief returns ID of gate represented by this gBlock
         * @return id of corresponding gate
         */
        const ID &getId() const;

        /**
         * @brief Returns bounding box of this gate on canvas in grid coordinates
         * @return AABB of this gate in grid coordinates
         */
        UI::Rect getRect() const;

        /**
         * @brief Returns pointer to corresponding GPort
         * @param isInput true if inputPort wanted, false if output
         * @param port index (same as in Gate)
         * @return pointer to corresponding GPort or nullptr if not found
         */
        std::shared_ptr<GPort> getGPort(bool isInput, Port port);

        /**
         * @brief returns GPort at given position in the GBlock
         * @param pos absolute position in canvas coordinates
         * @return GPort at position or nullptr if no such port exists
         */
        std::shared_ptr<GPort> getGPortAt(UI::Vec2 &pos) const;

        /**
         * @brief Updates position to new position.
         * @param pos new position for gBlock
         */
        void move(const UI::Vec2 pos);

        /**
         * @brief updates info about gate from model
         */
        void update();

        /**
         * @brief Checks if this block is beeing dragged
         * @return DRAGGED_FLAG
         */
        bool isDragged() const;

        /**
         * @brief Returns exact drag delta in canvas coordinates
         * @return
         */
        const UI::Vec2 &getDragDeltaExact() const;

    private:

        /**
         * @brief Renders Bezier between given ports at given blocks
         * @param ID1 ID for first endpoint
         * @param thisGPort port for first endpoint
         * @param otherId ID for second endpoint
         * @param otherPort ID for second endpoint
         */
        void renderWire(std::shared_ptr<GPort> thisGPort, ID otherId, Port otherPort);
    };

} // namespace Logicon

#endif //LOGICON_G_BLOCK_H
