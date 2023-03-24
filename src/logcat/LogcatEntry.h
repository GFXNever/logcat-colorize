#pragma once

#include <ctime>
#include <string>


#ifdef WIN32
using pid_t = unsigned;
#endif

struct LogTimestamp {
    std::tm time;
    int milliseconds;

    static LogTimestamp from(const std::string& timestampStr);
};

enum class LogLevel {
    Verbose,
    Debug,
    Info,
    Warning,
    Error,
    Fatal,
    Silent
};

LogLevel logLevelFromString(const std::string& string);

struct LogcatEntry {
    LogTimestamp timestamp;
    pid_t pid;
    pid_t tid;
    LogLevel level;
    std::string tag;
    std::string message;
};