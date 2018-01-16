//
// Created by Tooster on 2017-12-28.
//

#include "exceptions/wrongPortException.h"

namespace Logicon {
    wrongPortException::wrongPortException(ID id, Port port, bool isInput) : logiconException("") {
        std::string err = "Couldn't access ";
        err += isInput ? "input" : "output";
        err += " port '" + std::to_string(id) + "':'" + std::to_string(port) + "'";
        this->details(err);
    }
} // namespace Logicon
