#pragma once

#include <string>
#include <sstream>

namespace utils {
    std::string trim(const std::string& input);

    void strptime(std::istringstream& input, const std::string format, struct tm* tm);
}