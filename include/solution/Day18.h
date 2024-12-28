
#ifndef __AOC_DAY_18_H__
#define __AOC_DAY_18_H__

#include "Solution.h"
#include <set>

namespace aoc {

struct MemNode {
    static const size_t RC_MAX = 70;
    static size_t aStarKb(const MemNode &start,
        const std::set<std::pair<size_t, size_t>> &mem_grid);

    MemNode(size_t row, size_t col, size_t g_cost) : row(row), col(col), g_cost(g_cost){};

    size_t row{}, col{};
    size_t g_cost{};

    bool isValid(const std::set<std::pair<size_t, size_t>> &mem_grid) const;
    bool isDestination() const;
    size_t calcH() const;
    size_t calcF() const;
    std::vector<MemNode> getNeighbors() const;
};

class Day18 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::set<std::pair<size_t, size_t>> parseKb(const size_t num_lines,
        const std::vector<std::string> &lines);
    size_t getKillerByteIdx(const std::vector<std::string> &lines);
};
} // namespace aoc
#endif
