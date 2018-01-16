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
    class GBlock : public std::enable_shared_from_this<GBlock> {

        bool inited;                                            /// late create GPorts

        std::weak_ptr<GCircuit> parentGCircuit;                 /// Parent GCircuit
        std::shared_ptr<Gate> gate;                             /// Pointer to gate it represents

        UI::Vec2 position;                                      /// position in parent GCircuit in grid coordinates
        UI::Vec2 dimension;                                     /// Vector representing size of gBLock in grid coordinates
        Texture texture;                                        /// Current texture may change in input and switch
        ImColor color;                                          /// Display color

        std::vector<std::shared_ptr<GPort>> gInputs;            /// inputs
        std::vector<std::shared_ptr<GPort>> gOutputs;           /// outputs

        UI::Vec2 dragDeltaExact;                                /// drag delta in canvas coordinates

    public:
        bool GBLOCK_HOVERED_FLAG;                               /// flag saying the block is hovered and can be interacted with
        bool GBLOCK_DRAGGED_FLAG;                               /// flag saying the block is dragged


        /**
         * @brief Constructor for new GBlock
         * @param parentGCircuit parent circuit it belongs to
         * @param gate original Gate from model
         * @param relativePosition in grid coordinates on canvas
         */
        GBlock(std::shared_ptr<GCircuit> parentGCircuit, std::shared_ptr<Gate> gate, UI::Vec2 relativePosition);

        /**
         * @brief Renders the gBlock also checking if it is dragged
         * @param placementMode suggestion whether GBlock should respond to user interactions
         */
        void render();

        /**
         * @brief Returns shared pointer to gate this GBlock points to
         * @return returns shared pointer to gate
         */
        const std::shared_ptr<Gate> &getGate() const;

        /**
         * @brief Returns positions in grid coordinates of this gate
         * @return UI::Vec2 representing position on grid (upper left corner)
         */
        const UI::Vec2 &getPosition() const;

        /**
         * @brief Returns dimensions in grid coordinates of this gate
         * @return UI::Vec2 representing dimensions
         */
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
         * @brief Returns parent GCircuit that this gate belongs to
         * @return parent GCircuit
         */
        const std::weak_ptr<GCircuit> &getParentGCircuit() const;

        /**
         * @brief Returns exact drag delta in canvas coordinates
         * @return
         */
        const UI::Vec2 &getDragDeltaExact() const;

        /**
         * @brief Updates position to new position.
         * @param pos new position for gBlock
         */
        void move(const UI::Vec2 pos);
//-----------------------------------------------------------------------------
// INTERNAL
//-----------------------------------------------------------------------------
    private:

        /**
         * @brief Renders Bezier between given ports at given blocks
         * @param ID1 ID for first endpoint
         * @param thisGPort port for first endpoint
         * @param otherId ID for second endpoint
         * @param otherPort ID for second endpoint
         */
        void renderWire(std::shared_ptr<GPort> thisGPort, ID otherId, Port otherPort);

        /**
         * @brief Lazy init GPorts
         */
        void init();

    };

} // namespace Logicon

#endif //LOGICON_G_BLOCK_H
