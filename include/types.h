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
    typedef unsigned int    ID;                                         /// ID type identifying all blocks. IDs are >= 0, so anything < 0 can be used as flag (document it)
    typedef unsigned int    Port;                                       /// Represents port by it's index in corresponding array in `Gate`.
    typedef int             State;                                      /// Represents port state OFF(0) or ON(1). Engine can use other variables to indicate if state was calculated.
    typedef int             Tick;                                       /// Represents tick type.

    const unsigned int      GATE_TYPE_COUNT = 11;                       /// How many types of gates there is
    static const State      initialState = 0;                           /// Represents initial state of port

    // TODO: make extern and init in App::init()
    static unsigned int     gateInputsCount  [GATE_TYPE_COUNT]                 /// inputs count for GATE_TYPE corresponding gates
                            {1,1,1,2,2,2,2,2,2,0,0};
    static unsigned int     gateOutputsCount [GATE_TYPE_COUNT]                 /// outputs count for GATE_TYPE corresponding gates
                            {1,1,1,1,1,1,1,1,1,1,1};

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
        NOT, DELAY, SWITCH, AND, OR, XOR, NAND, NOR, XNOR, CLOCK, INPUT,
        NO_GATE = -1 /// Used by GCircuit - not in gate-placing mode
    };

    static int fromMilis(float x) { return (int) (x * 1000); }

    static float toMilis(int x) { return ((float) x) / 1000.0; }

} // namespace Logicon

#endif //LOGICON_TYPES_H
