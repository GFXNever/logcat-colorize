#pragma once

#include "filter/Filter.h"

#include <argparse/argparse.hpp>

#include <optional>

class FilterFactory {
public:
    static std::optional<Filter> create(const argparse::ArgumentParser& args);
};
