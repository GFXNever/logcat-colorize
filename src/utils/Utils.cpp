#include <iomanip>
#include "Utils.h"

std::string utils::trim(const std::string& input) {
    constexpr static auto WHITESPACE_CHARACTERS = " \r\n";
    const auto strBegin = input.find_first_not_of(WHITESPACE_CHARACTERS);
    if (strBegin == std::string::npos)
        return "";

    const auto strEnd = input.find_last_not_of(WHITESPACE_CHARACTERS);
    const auto strRange = strEnd - strBegin + 1;

    return input.substr(strBegin, strRange);
}

void utils::strptime(std::istringstream& input, const std::string format, struct tm *tm) {
    input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
    input >> std::get_time(tm, format.c_str());

    if (input.fail()) {
        input.clear();
    }
}
