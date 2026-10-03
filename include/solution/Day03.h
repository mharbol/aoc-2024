
#ifndef _AOC_DAY_03_H_
#define _AOC_DAY_03_H_

#include "Solution.h"

namespace aoc {
class Day03 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    size_t mulLine(const std::string &line);
    size_t mulLineDoDont(const std::string &line, bool &is_do);
};
} // namespace aoc
#endif
