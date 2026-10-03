
#ifndef _AOC_DAY_04_H_
#define _AOC_DAY_04_H_

#include "Solution.h"

namespace aoc {
class Day04 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    size_t xmasSearch(const std::vector<std::string> &lines, const int32_t row,
        const int32_t col, const int32_t right, const int32_t up);
    size_t xmasX(const char c1, const char c2);
};
} // namespace aoc
#endif
