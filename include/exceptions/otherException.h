//
// Created by Tooster on 2017-12-25.
//

#ifndef LOGICON_OTHEREXCEPTION_H
#define LOGICON_OTHEREXCEPTION_H

#include <exception>
#include <utility>
#include <types.h>

namespace Logicon {

    /**
     * Exception returned when trying to access wrong port
     */
    class otherException : std::exception {
        std::string details;
    public:
        // TODO pass string format with variadic number of arguments like in std::printf()
        explicit otherException(std::string details) : details(std::move(details)) {}

    private:
        const char *what() const throw() override {
            std::string err = "Logicon encountered some exception: \n";
            err += details;
            err += "'\n";
            return err.c_str();
        }
    };
} // namespace Logicon

#endif //LOGICON_OTHEREXCEPTION_H
