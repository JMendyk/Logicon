//
// Created by Tooster on 2017-12-24.
//

#ifndef LOGICON_MISSINGINPUTEXCEPTION_H
#define LOGICON_MISSINGINPUTEXCEPTION_H

#include <types.h>
#include "logiconException.h"

namespace Logicon {

    /**
     * Exception returned when trying to access wrong port
     */
    class wrongPortException : public Logicon::logiconException {

    public:
        explicit wrongPortException(ID id, Port port, bool isInput) : logiconException("") {
            std::string err = "Couldn't access ";
            err += isInput ? "input" : "output";
            err += " port '" + std::to_string(id) + "':'" + std::to_string(port) + "'\n";
            this->details(err);
        }
    };
} // namespace Logicon
#endif //LOGICON_MISSINGINPUTEXCEPTION_H
