//
// Created by Tooster on 2017-12-24.
//

#ifndef LOGICON_IDNOTFOUNDEXCEPTION_H
#define LOGICON_IDNOTFOUNDEXCEPTION_H


#include <exception>
#include <types.h>
#include <sstream>


namespace Logicon {
    /**
     * Exception returned if block with given ID was not found
     */
    class idNotFoundException : std::exception {
        ID id;

    public:
        explicit idNotFoundException(ID id) : id(id) {}

        const char *what() const throw() override {
            std::string err = "Couldn't find a gate with ID:'";
            err += std::to_string(id);
            err += "'\n";
            return err.c_str();
        }

    };
} // namespace Logicon


#endif //LOGICON_IDNOTFOUNDEXCEPTION_H
