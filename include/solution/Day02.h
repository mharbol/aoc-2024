
#ifndef _AOC_DAY_02_H_
#define _AOC_DAY_02_H_

#include "Solution.h"

namespace aoc {
class Day02 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    bool isSafe(const std::string &);
    bool isDampenSafe(const std::string &);
};
} // namespace aoc
#endif
