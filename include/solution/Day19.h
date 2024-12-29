
#ifndef __AOC_DAY_19_H__
#define __AOC_DAY_19_H__

#include "Solution.h"
#include <cstddef>
#include <map>
#include <string>

namespace aoc {
class Day19 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::string regexPart1(const std::vector<std::string> &lines) const;
    std::vector<std::string> parseTowels(const std::string &towels) const;
    bool subsMatch(const std::string &base, const std::string &substr, const size_t idx) const;
    bool isConstructable(const std::string &pattern, const size_t idx,
        const std::vector<std::string> &towels) const;
    size_t countConstructions(const std::string &pattern, const size_t idx,
        const std::vector<std::string> &towels, std::map<size_t, size_t> &cache) const;
};
} // namespace aoc
#endif
