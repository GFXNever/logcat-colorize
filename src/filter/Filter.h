#pragma once

#include <nlohmann/json.hpp>

#include "logcat/LogcatEntry.h"

#include "filter/matchers/Matcher.h"

class Filter {
public:
    explicit Filter(std::shared_ptr<Matcher> matcher);
    ~Filter() = default;

public:
    [[nodiscard]] bool pass(const LogcatEntry& entry) const;

private:
    std::shared_ptr<Matcher> m_matcher;
};
