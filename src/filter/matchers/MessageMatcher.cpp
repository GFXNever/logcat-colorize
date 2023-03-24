#include "MessageMatcher.h"

MessageMatcher::MessageMatcher(const nlohmann::json& json) : TextualMatcher(json) {

}

bool MessageMatcher::match(const LogcatEntry& entry) const {
    return TextualMatcher::match(entry.message);
}
