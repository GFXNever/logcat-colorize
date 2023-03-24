#include "PidMatcher.h"

PidMatcher::PidMatcher(const nlohmann::json& json) {
    for (auto& pidJson : json) {
        m_allowedPids.push_back(pidJson.get<pid_t>());
    }
}

bool PidMatcher::match(const LogcatEntry& entry) const {
    return std::find(m_allowedPids.begin(), m_allowedPids.end(), entry.pid) != m_allowedPids.end();
}
