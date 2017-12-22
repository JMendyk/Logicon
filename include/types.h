//
// Created by Tooster on 16.12.2017.
//

#ifndef LOGICON_TYPES_H
#define LOGICON_TYPES_H

#include <tuple>
#include "circuit.h"


/**
 * @brief File containing project-wide typedefs.
 *
 * All custom types are intuitive names without trailing underscores.
 * All types are written in BigCamel with some exceptions like ID acronym
 *
 * @warning Local (class specific) typedefs shouldn't be put there.
 * @warning Instead, they should be put in corresponding classes and have one trailing underscore: typedef int eg_
 */
namespace Logicon{
    /// ID_ type identifying all blocks
    typedef const unsigned int ID;
    /// represents port by it's index in corresponding array in `Gate`
    typedef unsigned int Port;
    /// represents port state ON or OFF
    typedef bool PortState;
    /// represents single connection as pair <ID, PortIndex>
    typedef std::pair<ID, Port> Connection;
    /// represents tick type
    typedef int Tick;
} // namespace Logicon

#endif //LOGICON_TYPES_H
