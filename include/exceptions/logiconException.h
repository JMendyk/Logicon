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
    class logiconException : public std::exception {
        std::string message;
        std::string circumstances;
        std::string description;

        void update() {
            this->message = "Logicon encountered an exception.\n";
            this->message.append(circumstances);
            this->message.append(description);
        }
    public:
        // TODO pass string format with variadic number of arguments like in std::printf()
        explicit logiconException(std::string details) : description(std::move(details)) { update(); }

        /**
         * Appends info about circumstances at the beginning.
         * @param circumstances  circumstances in which exception was thrown
         */
        void when(const std::string &circumstances) {
            this->circumstances.append(circumstances);
            update();
        }

        /**
         * Appends details at the end of the exception message.
         * @param details details to append to exception description
         */
        void details(const std::string &details) {
            this->description.append(details);
            update();
        }

        const char *what() const throw() override {
            return message.c_str();
        }
    };
} // namespace Logicon

#endif //LOGICON_OTHEREXCEPTION_H
