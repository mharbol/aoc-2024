
#ifndef __AOC_DAY_13_H__
#define __AOC_DAY_13_H__

#include "Solution.h"
#include <tuple>

namespace aoc {

struct Button {
    int64_t x;
    int64_t y;
};

class Day13 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::vector<std::tuple<Button, Button, Button>> parse(
        const std::vector<std::string> &lines);

    template <const uint64_t N>
    std::string solve(const std::vector<std::string> &lines);
};
} // namespace aoc
#endif
