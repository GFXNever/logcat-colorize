#include "LogcatEntry.h"

#include <stdexcept>

LogTimestamp LogTimestamp::from(const std::string& timestampStr) {
    constexpr static auto TIMESTAMP_FORMAT = "%d-%d %d:%d:%d.%3d";
    constexpr static auto AMOUNT_OF_SCANNED_VALUES = 6;

    LogTimestamp result {};
    int month, day, hour, minute, second;
    if (::sscanf(timestampStr.c_str(), TIMESTAMP_FORMAT, &month, &day, &hour, &minute, &second, &result.milliseconds)
            != AMOUNT_OF_SCANNED_VALUES) {
        throw std::runtime_error("Datetime format is invalid");
    }

    result.time = {
            .tm_sec = second,
            .tm_min = minute,
            .tm_hour = hour,
            .tm_mday = day,
            .tm_mon = month
    };

    return result;
}

LogLevel logLevelFromString(const std::string& string) {
    if (string == "verbose") {
        return LogLevel::Verbose;
    } else if (string == "debug") {
        return LogLevel::Debug;
    } else if (string == "info") {
        return LogLevel::Info;
    } else if (string == "warning") {
        return LogLevel::Warning;
    } else if (string == "error") {
        return LogLevel::Error;
    } else if (string == "fatal") {
        return LogLevel::Fatal;
    } else if (string == "silent") {
        return LogLevel::Silent;
    }

    throw std::runtime_error("Invalid log level string");
}