#include "Filter.h"

Filter::Filter(const nlohmann::json& filterScheme) {

}

bool Filter::pass(const LogcatEntry& entry) const {
    return false;
}
