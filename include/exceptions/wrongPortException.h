//
// Created by Tooster on 2017-12-24.
//

#ifndef LOGICON_MISSINGINPUTEXCEPTION_H
#define LOGICON_MISSINGINPUTEXCEPTION_H

#include <exception>
#include <types.h>

namespace Logicon {

    /**
     * Exception returned when trying to access wrong port
     */
    class wrongPortException : std::exception {
        ID id;
        Port port;
        bool input;

    public:
        explicit wrongPortException(ID id, Port port, bool isInput) : id(id), port(port), input(isInput) {}

        const char *what() const throw() override {
            std::string err = "Couldn't access ";
            err += input ? "input" : "output";
            err += " port '" + std::to_string(id);
            err += "':'" + std::to_string(port);
            err += "'\n";
            return err.c_str();
        }
    };
} // namespace Logicon
#endif //LOGICON_MISSINGINPUTEXCEPTION_H
