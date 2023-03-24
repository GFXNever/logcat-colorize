#pragma once

#include "Matcher.h"

#include <nlohmann/json.hpp>

class LogLevelMatcher : public Matcher {
public:
    explicit LogLevelMatcher(const nlohmann::json& json);

public:
    [[nodiscard]] bool match(const LogcatEntry& entry) const override;

private:
    std::vector<LogLevel> m_allowedLevels;
};
