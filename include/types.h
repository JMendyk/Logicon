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
    /// ID type identifying all blocks. IDs are >= 0, so anything < 0 can be used as some flag.
    /// (but even so, try to document places where ID is used in this way)
    typedef unsigned int ID;
    /// Represents port by it's index in corresponding array in `Gate`.
    typedef unsigned int Port;
    /// Represents port state OFF(0) or ON(1). Engine can use other variables to indicate if state was calculated.
    typedef int State;
    /// Represents tick type.
    typedef int Tick;

    /// Represents gate type. Used instead of runtime type deduction.
    enum GATE_TYPE {
        NOT, DELAY, SWITCH, AND, OR, XOR, NAND, NOR, XNOR, CLOCK, INPUT
    };

    /// inputs count for GATE_TYPE corresponding gates
    const unsigned int gateInputsCount[11]{1, 1, 1, 2, 2, 2, 2, 2, 2, 0, 0};

    /// outputs count for GATE_TYPE corresponding gates
    const unsigned int gateOutputsCount[11]{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    /// Represents initial state of port
    static const State initialState = 0;

    /// Represents single connection as pair <ID, PortIndex>.
    struct Connection {
        ID id;
        Port port;

        Connection(ID id, Port port) : id(id), port(port) {}

        bool operator==(const Connection &rhs) const {
            return id == rhs.id &&
                   port == rhs.port;
        }

        bool operator!=(const Connection &rhs) const {
            return !(rhs == *this);
        }
    };
} // namespace Logicon

#endif //LOGICON_TYPES_H
