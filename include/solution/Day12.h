
#ifndef __AOC_DAY_12_H__
#define __AOC_DAY_12_H__

#include "Solution.h"
#include <set>
#include <string>
#include <tuple>

namespace aoc {
class Day12 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    enum Direction { UP, DOWN, RIGHT, LEFT };

    int32_t ROW_MAX, COL_MAX;

    std::pair<size_t, size_t> floodFillRegion(const int32_t row, const int32_t col,
        std::vector<std::vector<bool>> &visited, const std::vector<std::string> &lines,
        const char id);

    size_t checkNeighborId(int32_t row, int32_t col, char id,
        const std::vector<std::string> &lines);

    std::pair<size_t, size_t> floodFillSides(const int32_t row, const int32_t col,
        std::vector<std::vector<bool>> &visited, const std::vector<std::string> &lines,
        const char id, std::set<std::tuple<int32_t, int32_t, Direction>> &visited_edges);

    size_t checkSides(int32_t row, int32_t col, const char id,
        const std::vector<std::string> &lines,
        std::set<std::tuple<int32_t, int32_t, Direction>> &visited_edges);

    bool isSide(int32_t row, int32_t col, const char id, Direction dir,
        const std::vector<std::string> &lines);
};
} // namespace aoc
#endif
