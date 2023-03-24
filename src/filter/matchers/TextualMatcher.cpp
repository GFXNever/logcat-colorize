#include <regex>
#include "TextualMatcher.h"

TextualMatcher::TextualMatcher(const nlohmann::json& json) {
    for (auto& patternJson : json) {
        auto pattern = patternJson["pattern"].get<std::string>();

        bool exact = false;
        if (patternJson.contains("mode")) {
            exact = patternJson["mode"].get<std::string>() == "exact";
        }

        bool caseInsensitive = false;
        if (patternJson.contains("caseInsensitive")) {
            caseInsensitive = patternJson["caseInsensitive"].get<bool>();
        }

        if (exact) {
            pattern = "^" + pattern + "$";
        }

        std::regex regex {};
        if (caseInsensitive) {
            regex = std::regex(pattern, std::regex_constants::icase);
        } else {
            regex = std::regex(pattern);
        }

        m_patterns.push_back(regex);
    }
}

bool TextualMatcher::match(const std::string& message) const {
    auto matchOperation = [&](const std::regex& pattern)-> bool {
        return std::regex_search(message, pattern);
    };

    return std::any_of(m_patterns.begin(), m_patterns.end(), matchOperation);
}
