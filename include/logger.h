//
// Created by rufus on 25.12.17.
//

#ifndef LOGICON_LOGGER_H
#define LOGICON_LOGGER_H

#include <fstream>
#include <iostream>
#include <cstdarg>
#include <string>
#include <cassert>

/**
*   @brief Singleton Logger Class.
*   @note Default logger file will be created in the same dir as built project.
*   @example Logger::err(" x var should be: %d and is: %d",x_should,x);
*/
class Logger {
public:
    /**
    *   @brief Logs debug message
    *   @param format string for the message to be logged.
    */
    static void debug(const char *format, ...);

    /**
    *   @brief Logs info message
    *   @param format string for the message to be logged.
    */
    static void info(const char *format, ...);

    /**
    *   @brief Logs warning message
    *   @param format string for the message to be logged.
    */
    static void warn(const char *format, ...);

    /**
    *   @brief Logs error message
    *   @param format string for the message to be logged.
    */
    static void err(const char *format, ...);

    /**
    *   @brief Initialize Logger with default filename
    */
    static void init();

    /**
    *   @brief Initialize Logger with provided filename
    *   @param filename filename of log file.
    */
    static void init(std::string filename);

private:
    /**
    *   Singleton logger class object pointer.
    **/
    static Logger *logger;

    /**
    *    Default constructor for the Logger class.
    */
    Logger();

    /**
    *    Constructor for the Logger class.
    *    @param filename filename of log file.
    */
    Logger(std::string filename);

    /**
    *   copy constructor for the Logger class.
    */
    Logger(const Logger &) = default; // copy constructor is private
    /**
    *   assignment operator for the Logger class.
    */
    Logger &operator=(const Logger &) { return *this; }; // assignment operator is private
    /**
    *   Log file name.
    **/
    std::string logFileName;
    /**
    *   Log file stream object.
    **/
    std::ofstream logFile;

    /**
    *   @brief Logs message of provided type
    *   @param entry_type type of message (ex. debug, warn, err)
    *   @param format string for the message to be logged
    *   @param args arguments for format
    */
    static void logEntry(std::string entry_type, const char *format, va_list args);

    static std::string formatted_time();
};

#endif //LOGICON_LOGGER_H