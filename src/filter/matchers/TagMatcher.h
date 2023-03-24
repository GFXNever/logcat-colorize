#pragma once

#include "TextualMatcher.h"

#include <nlohmann/json.hpp>

class TagMatcher : public TextualMatcher {
public:
    explicit TagMatcher(const nlohmann::json& json);

public:
    [[nodiscard]] bool match(const LogcatEntry& entry) const override;
};
