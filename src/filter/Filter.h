#pragma once

#include <nlohmann/json.hpp>

#include "logcat/LogcatEntry.h"

class Filter {
public:
    explicit Filter(const nlohmann::json& filterScheme);
    ~Filter() = default;

public:
    bool pass(const LogcatEntry& entry) const;
};
