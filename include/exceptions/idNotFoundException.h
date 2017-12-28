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
    class idNotFoundException : public Logicon::logiconException {

    public:
        explicit idNotFoundException(ID id) : logiconException("") {
            std::string desc = "Couldn't find a gate with ID:'" + std::to_string(id) + "'\n";
            this->details(desc);
        }

    };
} // namespace Logicon


#endif //LOGICON_IDNOTFOUNDEXCEPTION_H
