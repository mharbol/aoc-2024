
#ifndef __AOC_DAY_10_H__
#define __AOC_DAY_10_H__

#include "Solution.h"
#include <set>

namespace aoc {
class Day10 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    size_t distinctTrails(const std::vector<std::string> &lines, const int32_t row,
        const int32_t col, const char target);
    std::set<std::pair<int32_t, int32_t>> trailScore(const std::vector<std::string> &lines,
        const int32_t row, const int32_t col, const char target);
};
} // namespace aoc
#endif
