//
// Created by Tooster on 2017-12-28.
//
#include "exceptions/idNotFoundException.h"

namespace Logicon {
    idNotFoundException::idNotFoundException(ID id) : Logicon::logiconException("") {
        std::string desc = "Couldn't find a gate with ID:'" + std::to_string(id) + "'";
        this->details(desc);
    }

} // namespace Logicon
