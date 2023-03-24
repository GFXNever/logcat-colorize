#include "LogLevelMatcher.h"

LogLevelMatcher::LogLevelMatcher(const nlohmann::json& json) {
    for (auto& levelJson : json) {
        m_allowedLevels.push_back(logLevelFromString(levelJson.get<std::string>()));
    }
}

bool LogLevelMatcher::match(const LogcatEntry& entry) const {
    return std::find(m_allowedLevels.begin(), m_allowedLevels.end(), entry.level) != m_allowedLevels.end();
}
