#include "CompoundMatcher.h"

#include <algorithm>
#include <stdexcept>

CompoundLogicalOperation compoundLogicalOperationFromString(const std::string& string)  {
    if (string == "or") {
        return CompoundLogicalOperation::Or;
    } else if (string == "and") {
        return CompoundLogicalOperation::And;
    }

    throw std::runtime_error("Invalid concatenation mode");
}

CompoundMatcher::CompoundMatcher(const std::vector<std::shared_ptr<Matcher>>& matchers, CompoundLogicalOperation compoundOperation)
    :   m_matchers(matchers),
        m_compoundOperation(compoundOperation) {}

bool CompoundMatcher::match(const LogcatEntry& entry) const {
    auto matchOperation = [&](auto matcher) -> bool { return matcher->match(entry); };
    switch (m_compoundOperation) {
        case CompoundLogicalOperation::And:
            return std::all_of(m_matchers.begin(), m_matchers.end(), matchOperation);
        case CompoundLogicalOperation::Or:
            return std::any_of(m_matchers.begin(), m_matchers.end(), matchOperation);
    }

    throw std::runtime_error("Invalid compound logical operation");
}
