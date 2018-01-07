//
// Created by rufus on 25.12.17.
//

#include <ctime>
#include <utility>
#include "logger.h"

namespace Logicon {
    Logger *Logger::logger = nullptr;

    std::string Logger::formatted_time() {
        time_t rawtime;
        struct tm *timeinfo;
        char buffer[80];

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer, sizeof(buffer), "[%d-%m-%Y %H:%M:%S]", timeinfo);
        std::string str(buffer);
        return str;
    }

    void Logger::logEntry(std::string entry_type, const char *format, va_list args) {
        // if not initialized, initialize with default settings;
        if (logger == nullptr)
            Logger::init();

        int log_msg_len = vsnprintf(nullptr, 0, format, args) + 1;
        char *log_msg = new char[log_msg_len];

        vsnprintf(log_msg, log_msg_len, format, args);
        std::string prefix = formatted_time() + "[" + entry_type + "]: ";
        // fills empty space after every newline with length of prefix empty space
        std::string filler(prefix.length(), ' ');
        std::string log_msg_tabbed(log_msg);
        for (int i = 0; i < log_msg_tabbed.length() - 1; ++i)
            if (log_msg_tabbed[i] == '\n')
                log_msg_tabbed.insert(i + 1, filler);
        // logger->logFile << formatted_time() << "[" << entry_type << "]:\t";
        logger->logFile << prefix << log_msg_tabbed << "\n";

        delete[] log_msg;
    }

    void Logger::debug(const char *format, ...) {
        va_list args;
        va_start(args, format);
        logEntry("DEBUG", format, args);
        va_end(args);
    }

    void Logger::info(const char *format, ...) {
        va_list args;
        va_start(args, format);
        logEntry("INFO", format, args);
        va_end(args);
    }

    void Logger::warn(const char *format, ...) {
        va_list args;
        va_start(args, format);
        logEntry("WARN", format, args);
        va_end(args);
    }

    void Logger::err(const char *format, ...) {
        va_list args;
        va_start(args, format);
        logEntry("ERR", format, args);
        va_end(args);
    }

    Logger::Logger(std::string filename) {
        logFileName = std::move(filename);
        logFile.rdbuf()->pubsetbuf(nullptr, 0); // disable buffering
        logFile.open(logFileName, std::ios::out | std::ios::app);
    }

    void Logger::init() {
        Logger::init("Logicon.log");
    }

    void Logger::init(std::string filename) {
        if (logger == nullptr)
            Logger::logger = new Logger(std::move(filename));
    }
} // namespace Logicon