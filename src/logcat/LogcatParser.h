#pragma once

#include "LogcatEntry.h"

#include <string>
#include <regex>
#include <optional>

class LogcatParser {
public:
    struct InvalidLogcatLineException : std::exception {
        InvalidLogcatLineException(const std::string& line) {
            this->line = line;
        }

        std::string line;
    };

public:
    static std::optional<LogcatEntry> parseLine(const std::string_view& line);

private:
    static LogTimestamp consumeTimestamp(std::string& line);
    static pid_t consumePid(std::string& line);
    static LogLevel consumeLogLevel(std::string& line);
    static std::string consumeTag(std::string& line);
    static std::string consumeMessage(std::string& line);

    static std::string consumeRegex(std::string& line, const std::string& pattern);
};