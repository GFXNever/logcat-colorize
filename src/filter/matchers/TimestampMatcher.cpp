#include <iostream>
#include "TimestampMatcher.h"

bool operator>(const LogTimestamp& lhs, const LogTimestamp& rhs);
bool operator<=(const LogTimestamp& lhs, const LogTimestamp& rhs);
bool operator>=(const LogTimestamp& lhs, const LogTimestamp& rhs);

TimestampMatcher::TimestampMatcher(const nlohmann::json& config) {
    for (auto range : config["ranges"]) {
        std::optional<LogTimestamp> low, high;

        if (range.contains("low")) {
            low = LogTimestamp::from(range["low"].get<std::string>());
        }
        if (range.contains("high")) {
            high = LogTimestamp::from(range["high"].get<std::string>());
        }

        if (low && high && *low > *high) {
            throw std::runtime_error("Invalid timestamp filter - high is lower than low");
        }

        if (!low && !high) {
            throw std::runtime_error("Timestamp filtering must contain at least one boundary");
        }

        m_conditions.push_back({low, high});
    }
}

bool TimestampMatcher::checkTimeCondition(const TimestampCondition& condition, const LogcatEntry& entry) const {
    if (!condition.low) {
        return entry.timestamp <= *condition.high;
    }

    if (!condition.high) {
        return entry.timestamp >= *condition.low;
    }

    return *condition.low <= entry.timestamp && entry.timestamp <= *condition.high;
}

bool TimestampMatcher::match(const LogcatEntry& entry) const {
    auto matchOperation = [&](const TimestampCondition& condition) -> bool {
        return checkTimeCondition(condition, entry);
    };

    return std::any_of(m_conditions.begin(), m_conditions.end(), matchOperation);
}

time_t castTime(std::tm time) {
    return std::mktime(&time);
}

bool operator>(const LogTimestamp& lhs, const LogTimestamp& rhs) {
    auto firstTime = castTime(lhs.time);
    auto secondTime = castTime(rhs.time);

    auto diff = std::difftime(firstTime, secondTime);
    if (diff > 0) {
        return true;
    } else if (diff == 0) {
        return lhs.milliseconds > rhs.milliseconds;
    }

    return false;
}

bool operator<=(const LogTimestamp& lhs, const LogTimestamp& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const LogTimestamp& lhs, const LogTimestamp& rhs) {
    return !(rhs > lhs);
}