//
// Created by Tooster on 16.12.2017.
//

#ifndef LOGICON_TYPES_H
#define LOGICON_TYPES_H

#include <tuple>
#include <map>
#include <list>
#include <memory>
#include <string>
#include <vector>
#include "data.h"


/**
 * @brief File containing project-wide typedefs and structs too small to make separate classes for them.
 *
 * All custom types are intuitive names without trailing underscores.
 * All types are written in BigCamel with some exceptions like ID acronym
 *
 * @warning Local (class specific) typedefs shouldn't be put there.
 * @warning Instead, they should be put in corresponding classes and have one trailing underscore: typedef int eg_
 */
namespace Logicon {


    // @formatter:off
    typedef int             ID;                                         /// ID type identifying all blocks. IDs are >= 0, so anything < 0 can be used as flag (document it)
    typedef int             Port;                                       /// Represents port by it's index in corresponding array in `Gate`.
    typedef int             State;                                      /// Represents port state OFF(0) or ON(1). Engine can use other variables to indicate if state was calculated.
    typedef int             Tick;                                       /// Represents tick type.

    const unsigned int      GATE_TYPE_COUNT = 13;                       /// How many types of gates there is
    static const State      initialState = 0;                           /// Represents initial state of port

    // TODO: make extern and init in App::init()
    static unsigned int     gateInputsCount  [GATE_TYPE_COUNT]                 /// inputs count for GATE_TYPE corresponding gates
                            {1,     // NOT
                             1,     // DELAY
                             1,     // SWITCH_ON
                             1,     // SWITCH_OFF
                             2,     // AND
                             2,     // OR
                             2,     // XOR
                             2,     // NAND
                             2,     // NOR
                             2,     // XNOR
                             0,     // CLOCK
                             0,     // INPUT_ON
                             0      // INPUT_OFF
                            };
    static unsigned int     gateOutputsCount [GATE_TYPE_COUNT]                 /// outputs count for GATE_TYPE corresponding gates
                            {1,     // NOT
                             1,     // DELAY
                             1,     // SWITCH_ON
                             1,     // SWITCH_OFF
                             1,     // AND
                             1,     // OR
                             1,     // XOR
                             1,     // NAND
                             1,     // NOR
                             1,     // XNOR
                             1,     // CLOCK
                             1,     // INPUT_ON
                             1      // INPUT_OFF
                            };

    // @formatter:on

    /// Represents single connection as pair <ID, PortIndex>.
    struct Connection {
        ID id;
        Port port;

        Connection(ID id, Port port) : id(id), port(port) {}

        bool operator==(const Connection &rhs) const { return id == rhs.id && port == rhs.port; }

        bool operator!=(const Connection &rhs) const { return !(rhs == *this); }
    };

    enum GATE_TYPE {                                                    /// Represents gate type. Used instead of runtime type deduction.
        NOT, DELAY, SWITCH_ON, SWITCH_OFF, AND, OR, XOR, NAND, NOR, XNOR, CLOCK, INPUT_ON, INPUT_OFF
    };

    static int fromMilis(float x) { return (int) (x * 1000); }

    static float toMilis(int x) { return ((float) x) / 1000.0; }

} // namespace Logicon

#endif //LOGICON_TYPES_H
