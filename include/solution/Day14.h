
#ifndef __AOC_DAY_14_H__
#define __AOC_DAY_14_H__

#include "Solution.h"
#include <cstdint>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace aoc {
class Robot {

public:
    int32_t p_row, p_col, v_row, v_col;
    Robot(int32_t p_row, int32_t p_col, int32_t v_row, int32_t v_col)
        : p_row(p_row), p_col(p_col), v_row(v_row), v_col(v_col) {}
    ~Robot() = default;
    void teleport(int32_t seconds, int32_t width, int32_t height);
};

class Day14 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    int32_t WIDTH{}, HEIGHT{};

    std::vector<Robot> parse(const std::vector<std::string> &lines);
    size_t prodQuad(const std::vector<Robot> &robots);
    size_t countSurrounded(const std::set<std::pair<int32_t, int32_t>> &);
};
} // namespace aoc
#endif
