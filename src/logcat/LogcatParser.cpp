#include "LogcatParser.h"
#include "utils/Utils.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <chrono>

std::optional<LogcatEntry> LogcatParser::parseLine(const std::string_view& line) {
    try {
        std::string cursor(line);
        return std::make_optional<LogcatEntry>({
                consumeTimestamp(cursor),
                consumePid(cursor),
                consumePid(cursor),
                consumeLogLevel(cursor),
                consumeTag(cursor),
                consumeMessage(cursor)
        });
    } catch (const InvalidLogcatLineException& e) {
        return std::nullopt;
    }
}

LogTimestamp LogcatParser::consumeTimestamp(std::string& line) {
    constexpr static auto TIMESTAMP_PATTERN = "^[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2}\\.[0-9]{3}";
    constexpr static auto TIMESTAMP_FORMAT = "%d-%d %d:%d:%d.%3d";

    auto timestampStr = consumeRegex(line, TIMESTAMP_PATTERN);

    LogTimestamp result {};
    int month, day, hour, minute, second;
    ::sscanf(timestampStr.c_str(), TIMESTAMP_FORMAT, &month, &day, &hour, &minute, &second, &result.milliseconds);

    result.time = {
            .tm_sec = second,
            .tm_min = minute,
            .tm_hour = hour,
            .tm_mday = day,
            .tm_mon = month,
    };

    return result;
}

pid_t LogcatParser::consumePid(std::string& line) {
    constexpr static auto PID_PATTERN = "^[0-9]+";
    auto pidStr = consumeRegex(line, PID_PATTERN);
    return std::stoi(pidStr);
}

LogLevel LogcatParser::consumeLogLevel(std::string& line) {
    constexpr static auto LOGLEVEL_PATTERN = "^(V|D|I|W|E|F|S)";
    auto levelStr = consumeRegex(line, LOGLEVEL_PATTERN);

    switch(levelStr[0]) {
        case 'V': {
            return LogLevel::Verbose;
        }
        case 'D': {
            return LogLevel::Debug;
        }
        case 'I': {
            return LogLevel::Info;
        }
        case 'W': {
            return LogLevel::Warning;
        }
        case 'E': {
            return LogLevel::Error;
        }
        case 'F': {
            return LogLevel::Fatal;
        }
        case 'S': {
            return LogLevel::Silent;
        }
        default: {
            break;
        }
    }

    throw InvalidLogcatLineException(levelStr);
}

std::string LogcatParser::consumeTag(std::string& line) {
    constexpr static auto TAG_PATTERN = "^[^:]+:";
    auto tag = consumeRegex(line, TAG_PATTERN);
    return utils::trim(tag.substr(0, tag.length() - 1));
}

std::string LogcatParser::consumeMessage(std::string& line) {
    return line;
}

std::string LogcatParser::consumeRegex(std::string& line, const std::string& pattern) {
    std::smatch match;
    if (!std::regex_search(line, match, std::regex(pattern))) {
        throw InvalidLogcatLineException(line);
    }

    std::string result = match[0].str();
    line = utils::trim(match.suffix());
    return result;
}

