#include "FilterFactory.h"

#include <nlohmann/json.hpp>

std::optional<Filter> FilterFactory::create(const argparse::ArgumentParser& args) {
    auto filterJson = args.present<nlohmann::json>("filter");
    if (!filterJson) {
        return std::nullopt;
    }

    return std::make_optional<Filter>(*filterJson);
}