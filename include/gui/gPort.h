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

    class BlocksWidget;

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

        bool GPORT_DRAGGED_FLAG;                                       /// flag saying that a connection is being drawn
        bool GPORT_HOVERED_FLAG;                                    /// true if mouse interacts with GPort, false otherwise
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
        void render(const UI::Vec2 &gBlockPos, State state);

        /**
         * @brief Returns bounding box of this GPort in Grid coordinates relative to parent(with floats if GPort Margin is not zero)
         * @return AABB of GPort in grid coordinates
         */
        UI::Rect getRect();

    public:
        static std::string getHovered();

        static std::string getDragged();
    };
} // namespace Logicon

#endif //LOGICON_GPORT_H