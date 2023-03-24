#include "FilterFactory.h"

#include "filter/matchers/CompoundMatcher.h"
#include "filter/matchers/TimestampMatcher.h"
#include "filter/matchers/LogLevelMatcher.h"
#include "filter/matchers/PidMatcher.h"
#include "filter/matchers/TagMatcher.h"
#include "filter/matchers/MessageMatcher.h"

#include <nlohmann/json.hpp>

template<typename T>
concept MatcherType = std::is_base_of_v<Matcher, T>;

template<MatcherType T>
std::optional<std::shared_ptr<Matcher>> parseAndCreateMatcher(const nlohmann::json& filterJson, const std::string& matcherKey) {
    if (filterJson.contains(matcherKey)) {
        auto matcher = std::make_shared<T>(filterJson[matcherKey]);
        return std::make_optional<std::shared_ptr<T>>(std::move(matcher));
    }

    return std::nullopt;
}

std::shared_ptr<Matcher> parseMatcher(const nlohmann::json& json) {
    std::vector<std::optional<std::shared_ptr<Matcher>>> potentialMatchers;

    potentialMatchers.push_back(parseAndCreateMatcher<TimestampMatcher>(json, "timestamp"));
    potentialMatchers.push_back(parseAndCreateMatcher<LogLevelMatcher>(json, "level"));
    potentialMatchers.push_back(parseAndCreateMatcher<PidMatcher>(json, "pid"));
    potentialMatchers.push_back(parseAndCreateMatcher<TagMatcher>(json, "tag"));
    potentialMatchers.push_back(parseAndCreateMatcher<MessageMatcher>(json, "message"));

    std::vector<std::shared_ptr<Matcher>> matchers;
    for (auto& matcher : potentialMatchers) {
        if (matcher) {
            matchers.push_back(std::move(*matcher));
        }
    }

    return std::make_shared<CompoundMatcher>(matchers, CompoundLogicalOperation::And);
}

std::shared_ptr<Matcher> parseTopLevelMatcher(const nlohmann::json& json) {
    CompoundLogicalOperation operation = CompoundLogicalOperation::Or;
    if (json.contains("mode")) {
        operation = compoundLogicalOperationFromString(json["mode"].get<std::string>());
    }

    std::vector<std::shared_ptr<Matcher>> matchers;
    for (const auto& matcherJson : json["filters"]) {
        matchers.emplace_back(parseMatcher(matcherJson));
    }

    return std::make_shared<CompoundMatcher>(matchers, operation);
}

std::optional<Filter> FilterFactory::create(const argparse::ArgumentParser& args) {
    auto filterJson = args.present<nlohmann::json>("filter");
    if (!filterJson) {
        return std::nullopt;
    }

    return std::make_optional<Filter>(parseTopLevelMatcher((*filterJson)[0]));
}