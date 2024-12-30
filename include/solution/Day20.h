
#ifndef __AOC_DAY_20_H__
#define __AOC_DAY_20_H__

#include "Solution.h"

namespace aoc {
class Day20 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::vector<std::pair<int32_t, int32_t>> getPath(std::vector<std::string> lines,
        const int32_t start_row, const int32_t start_col, const int32_t end_row,
        const int32_t end_col) const;
    std::tuple<int32_t, int32_t, int32_t, int32_t> getStartEnd(
        const std::vector<std::string> &lines) const;
    size_t countReductions(const std::vector<std::pair<int32_t, int32_t>> &points,
        const int32_t cheat_time, const int32_t target) const;
};
} // namespace aoc
#endif
