#pragma once

#include "Matcher.h"

#include <nlohmann/json.hpp>

class TimestampMatcher : public Matcher {
private:
    struct TimestampCondition {
        std::optional<LogTimestamp> low;
        std::optional<LogTimestamp> high;
    };

public:
    explicit TimestampMatcher(const nlohmann::json& config);

public:
    [[nodiscard]] bool match(const LogcatEntry& entry) const override;

private:
    [[nodiscard]] bool checkTimeCondition(const TimestampCondition& condition, const LogcatEntry& entry) const;

private:
    std::vector<TimestampCondition> m_conditions;
};
