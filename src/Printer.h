#pragma once

#include "logcat/LogcatEntry.h"

class Printer {
public:
    Printer() = default;
    ~Printer() = default;

public:
    void printLine(const std::string& line) const;
    void printFormatted(const LogcatEntry& log) const;

private:
    void printTimestamp(std::ostream& out, const LogcatEntry& log) const;
    void printPid(std::ostream& out, const LogcatEntry& log) const;
    void printLogLevel(std::ostream& out, const LogcatEntry& log) const;
    void printTag(std::ostream& out, const LogcatEntry& log) const;
    void printMessage(std::ostream& out, const LogcatEntry& log) const;
};
