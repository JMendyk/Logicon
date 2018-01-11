//
// Created by Tooster on 2017-12-31.
//

#ifndef LOGICON_GPORT_H
#define LOGICON_GPORT_H

#include <types.h>
#include "gUtils.h"

namespace Logicon {

    // FORWARD DECLARATION
    class GCircuit;

    class GPort {
        std::string uniqeElemId;

        static constexpr const char *DRAGDROP_FROM_INPUT = "gp_f_i";
        static constexpr const char *DRAGDROP_FROM_OUTPUT = "gp_f_o";

    public:

        // @formatter:off
        const std::weak_ptr<GCircuit> parentGCircuit;               /// weak pointer to parent circuit (to enable usage of connect, disconnect)
        const ID gateId;                                            /// ID of block it belongs to
        const Port port;                                            /// index of port it represents
        const bool isInput;                                         /// represents type of port
        const UI::Vec2 relativePosition;                            /// Position in GCircuit in grid coordinates

        bool DRAGGING_FLAG;                                         /// flag saying the block is dragged
        // @formatter:on
        /**
         * @brief Constructor for GPort.
         * @param isInput true if the port is an input, false if it is an output
         * @param parentGCircuit weak pointer to parent GBlock
         * @param gateId id of parent gate
         * @param index index in parent GBlock
         * @param parentPos position in parent
         */
        GPort(bool isInput, std::shared_ptr<GCircuit> parentGCircuit, ID gateId, Port index, UI::Vec2 relativePosition);

        /**
         * @bief Run when dragging wire from port to port.
         */
        void dragging();

        /**
         * @brief Renders GPort.
         * @param should_interact suggestion whether GBlock should respond to user interactions
         */
        void render(const UI::Vec2 &gBlockPos, bool should_interact);

        /**
         * @brief Returns bounding box of this GPort in Grid coordinates relative to parent(with floats if GPort Margin is not zero)
         * @return AABB of GPort in grid coordinates
         */
        UI::Rect getRect();

        bool isDragged() const;
    };
} // namespace Logicon

#endif //LOGICON_GPORT_H