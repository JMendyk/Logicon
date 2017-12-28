//
// Created by Tooster on 2017-12-25.
//

#ifndef LOGICON_OTHEREXCEPTION_H
#define LOGICON_OTHEREXCEPTION_H

#include <stdexcept>
#include <types.h>

namespace Logicon {

    /**
     * Exception returned when trying to access wrong port
     */
    class logiconException : public std::exception {
        std::string message;
        std::string circumstances;
        std::string description;


        void update();
    public:
        ///Constructor
        explicit logiconException(std::string details);

        /**
         * Appends info about circumstances at the beginning.
         * @param circumstances  circumstances in which exception was thrown
         */
        void when(const std::string &circumstances);

        /**
         * Appends details at the end of the exception message.
         * @param details details to append to exception description
         */
        void details(const std::string &details);

        const char *what() const throw() override;
    };
} // namespace Logicon

#endif //LOGICON_OTHEREXCEPTION_H
