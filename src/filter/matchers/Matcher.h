#pragma once

#include "logcat/LogcatEntry.h"

class Matcher {
public:
    Matcher() = default;
    virtual ~Matcher() = default;

public:
    virtual bool match(const LogcatEntry& entry) const = 0;
};