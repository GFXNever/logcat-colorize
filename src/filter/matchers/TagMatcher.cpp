#include "TagMatcher.h"

TagMatcher::TagMatcher(const nlohmann::json& json) : TextualMatcher(json) {

}

bool TagMatcher::match(const LogcatEntry& entry) const {
    return TextualMatcher::match(entry.tag);
}
