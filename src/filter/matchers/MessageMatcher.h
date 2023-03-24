#pragma once

#include "TextualMatcher.h"

#include <nlohmann/json.hpp>

class MessageMatcher : public TextualMatcher {
public:
    explicit MessageMatcher(const nlohmann::json& json);

public:
    [[nodiscard]] bool match(const LogcatEntry& entry) const override;
};
