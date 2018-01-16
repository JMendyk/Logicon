//
// Created by Tooster on 2017-12-31.
//

#ifndef LOGICON_GPORT_H
#define LOGICON_GPORT_H

#include <types.h>
#include "gUtils.h"

namespace Logicon {

    // FORWARD DECLARATION
    class BlocksWidget;

    class GBlock;

    class GPort {
        // @formatter:off
        std::string                     uniqeElemId;

        static constexpr const char    *DRAGDROP_FROM_INPUT = "gp_f_i";
        static constexpr const char    *DRAGDROP_FROM_OUTPUT = "gp_f_o";

        bool                            GPORT_DRAGGED_FLAG;                     /// flag saying that a connection is being drawn
        bool                            GPORT_HOVERED_FLAG;                     /// true if mouse interacts with GPort, false otherwise
    public:
        const std::weak_ptr<GBlock>     parentGBlock;                           /// weak pointer to parent circuit (to enable usage of connect, disconnect)
        const UI::Vec2                  relativePosition;                       /// relative position to GBlock's LU corner in grid coordinates

        const bool                      isInput;                                /// represents type of port
        const Port                      port;                                   /// index of port it represents
        // @formatter:on

        /**
         * @brief Constructor for GPort.
         * @param isInput true if the port is an input, false if it is an output
         * @param parentGBlock weak pointer to parent GBlock
         * @param gateId id of parent gate
         * @param index index in parent GBlock
         */
        GPort(std::shared_ptr<Logicon::GBlock> parentGBlock, bool isInput, Port index);

        /**
         * @brief Renders GPort.
         */
        void render();

    public:
        static std::string getHovered();

        static std::string getDragged();
    };
} // namespace Logicon

#endif //LOGICON_GPORT_H