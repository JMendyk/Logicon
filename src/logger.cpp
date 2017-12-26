//
// Created by rufus on 25.12.17.
//

#include <ctime>
#include "logger.h"

Logger *Logger::logger = nullptr;

std::string Logger::formatted_time() {
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
    std::string str(buffer);
    return str;
}

void Logger::logEntry(std::string entry_type, const char *format, va_list args) {
    assert(logger != nullptr && "Logger must be initialized using Logger::init before usage");

    int log_msg_len = vsnprintf(nullptr, 0, format, args) + 1;
    char *log_msg = new char[log_msg_len];

    vsnprintf(log_msg, log_msg_len, format, args);
    logger->logFile << formatted_time() << "[" << entry_type << "]:\t";
    logger->logFile << log_msg << "\n";

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
    logFileName = filename;
    logFile.rdbuf()->pubsetbuf(0, 0); // disable buffering
    logFile.open(logFileName, std::ios::out | std::ios::app);
}

void Logger::init() {
    Logger::init("Logicon.log");
}

void Logger::init(std::string filename) {
    assert(logger == nullptr && "Logger must not be initalized multiple times");
    Logger::logger = new Logger(filename);
}