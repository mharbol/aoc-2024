
#ifndef __AOC_DAY_06_H__
#define __AOC_DAY_06_H__

#include "Solution.h"
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace aoc {
class Day06 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    int32_t guard_row;
    int32_t guard_col;
    void getGuardPos(const std::vector<std::string> &);
    std::set<std::pair<size_t, size_t>> walkAndRecord(const std::vector<std::string> &);
    size_t loops(const std::vector<std::string> &);
    enum Direction { UP, DOWN, RIGHT, LEFT };
};
} // namespace aoc
#endif
