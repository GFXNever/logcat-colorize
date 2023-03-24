#pragma once

#include "Matcher.h"

#include <nlohmann/json.hpp>

#include <regex>
#include <vector>

class TextualMatcher : public Matcher {
public:
    explicit TextualMatcher(const nlohmann::json& json);

protected:
    [[nodiscard]] bool match(const std::string& message) const;

private:
    std::vector<std::regex> m_patterns;
};
