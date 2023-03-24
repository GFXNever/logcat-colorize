#pragma once

#include "Matcher.h"

#include <vector>
#include <memory>
#include <stdexcept>

enum class CompoundLogicalOperation {
    And,
    Or
};

CompoundLogicalOperation compoundLogicalOperationFromString(const std::string& string);

class CompoundMatcher : public Matcher {
public:
    explicit CompoundMatcher(const std::vector<std::shared_ptr<Matcher>>& matchers, CompoundLogicalOperation compoundOperation);

public:
    [[nodiscard]] bool match(const LogcatEntry& entry) const override;

private:
    std::vector<std::shared_ptr<Matcher>> m_matchers;
    CompoundLogicalOperation m_compoundOperation;
};
