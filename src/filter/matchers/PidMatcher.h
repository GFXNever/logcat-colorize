#pragma once

#include "Matcher.h"

#include <nlohmann/json.hpp>

class PidMatcher : public Matcher {
public:
    explicit PidMatcher(const nlohmann::json& json);

public:
    [[nodiscard]] bool match(const LogcatEntry& entry) const override;

private:
    std::vector<pid_t> m_allowedPids;
};
