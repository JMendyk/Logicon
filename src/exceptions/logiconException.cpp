//
// Created by Tooster on 2017-12-28.
//

#include "exceptions/logiconException.h"

namespace Logicon {

    void logiconException::update() {
        this->message = "Logicon encountered an exception:";
        if (!circumstances.empty())
            this->message += "\n  circumstances:" + this->circumstances;
        if (!description.empty())
            this->message += "\n  details:" + this->description;
    }

    logiconException::logiconException(std::string details) : description(std::move(details)) { update(); }

    void logiconException::when(const std::string &circumstances) {
        this->circumstances += "\n    " + circumstances;
        update();
    }

    void logiconException::details(const std::string &details) {
        this->description += "\n    " + details;
        update();
    }

    const char *logiconException::what() const throw() {
        return message.c_str();
    }
} // namespace Logicon