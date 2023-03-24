#include "Filter.h"

#include <utility>

Filter::Filter(std::shared_ptr<Matcher> matcher) : m_matcher(std::move(matcher)) {

}

bool Filter::pass(const LogcatEntry& entry) const {
    return m_matcher->match(entry);
}
