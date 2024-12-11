
#ifndef __AOC_DAY_11_H__
#define __AOC_DAY_11_H__

#include "Solution.h"
#include <map>
#include <string>
#include <utility>

namespace aoc {
class Day11 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::map<std::pair<uint64_t, size_t>, size_t> cache{};

    std::vector<uint64_t> parse(const std::string &);
    void blink(std::vector<uint64_t> &);
    size_t digitSplit(uint64_t);
    size_t expandStone(uint64_t stone, size_t remaining);
};
} // namespace aoc
#endif
