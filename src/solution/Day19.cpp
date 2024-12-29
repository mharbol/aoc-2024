
#include "solution/Day19.h"
#include <regex>
#include <sstream>

namespace aoc {

std::string Day19::part1(const std::vector<std::string> &lines) {
    size_t acc{};
    auto iter = lines.begin();
    const auto towels = parseTowels(*iter);
    ++iter;
    while (++iter != lines.end()) {
        acc += isConstructable(*iter, 0, towels);
    }
    return std::to_string(acc);
}

std::string Day19::part2(const std::vector<std::string> &lines) {
    size_t acc{};
    auto iter = lines.begin();
    const auto towels = parseTowels(*iter);
    ++iter;
    while (++iter != lines.end()) {
        std::map<size_t, size_t> cache{};
        acc += countConstructions(*iter, 0, towels, cache);
    }
    return std::to_string(acc);
}

std::vector<std::string> Day19::parseTowels(const std::string &towels) const {

    std::vector<std::string> ret{};
    size_t last_comma{};
    size_t comma_idx = towels.find(", ");

    while (std::string::npos != comma_idx) {
        ret.push_back(towels.substr(last_comma, comma_idx - last_comma));
        last_comma = comma_idx + 2;
        comma_idx = towels.find(", ", last_comma + 1);
    }
    ret.push_back(towels.substr(last_comma, towels.size() - last_comma));
    return ret;
}

bool Day19::isConstructable(const std::string &pattern, const size_t idx,
    const std::vector<std::string> &towels) const {

    if (pattern.size() == idx) {
        return true;
    }
    for (const auto &towel : towels) {
        if (subsMatch(pattern, towel, idx)) {
            if (isConstructable(pattern, idx + towel.size(), towels)) {
                return true;
            }
        }
    }
    return false;
}

bool Day19::subsMatch(const std::string &base, const std::string &substr, size_t idx) const {

    if (base.size() < substr.size() + idx) {
        return false;
    }
    size_t subs_idx{};
    while (subs_idx < substr.size()) {
        if (base.at(idx++) != substr.at(subs_idx++)) {
            return false;
        }
    }
    return true;
}

size_t Day19::countConstructions(const std::string &pattern, const size_t idx,
    const std::vector<std::string> &towels, std::map<size_t, size_t> &cache) const {

    if (cache.contains(idx)) {
        return cache.at(idx);
    }
    size_t acc{};
    for (const auto &towel : towels) {
        if (subsMatch(pattern, towel, idx)) {
            if (pattern.size() == idx + towel.size()) {
                acc += 1;
            } else {
                acc += countConstructions(pattern, idx + towel.size(), towels, cache);
            }
        }
    }
    cache[idx] = acc;
    return acc;
}

std::string Day19::regexPart1(const std::vector<std::string> &lines) const {
    std::stringstream ss{};
    auto iter = lines.begin();
    ss << "^(";
    for (const auto &towel : parseTowels(*iter)) {
        ss << "(" << towel << ")|";
    }
    ss << "+$";
    std::string regex_pattern = ss.str();
    regex_pattern[regex_pattern.size() - 3] = ')';
    const std::regex pattern(regex_pattern);
    size_t acc{};
    ++iter;
    while (++iter != lines.end()) {
        acc += std::regex_match(*iter, pattern);
    }
    return std::to_string(acc);
}
} // namespace aoc
