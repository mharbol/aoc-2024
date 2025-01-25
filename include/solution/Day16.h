
#ifndef __AOC_DAY_16_H__
#define __AOC_DAY_16_H__

#include "Solution.h"
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace aoc {
struct MazeFrame {
    size_t row{};
    size_t col{};
    int32_t dr = 0;
    int32_t dc = 1;
    size_t score{};
    std::set<std::pair<size_t, size_t>> history{};

    MazeFrame() = default;
    MazeFrame(size_t row, size_t col, int32_t dr, int32_t dc, size_t score)
        : row(row), col(col), dr(dr), dc(dc), score(score) {}
    MazeFrame(size_t row, size_t col, int32_t dr, int32_t dc, size_t score,
        std::set<std::pair<size_t, size_t>> history)
        : row(row), col(col), dr(dr), dc(dc), score(score), history(history) {}

    inline bool operator>(const MazeFrame &rhs) const {
        return score > rhs.score;
    }
    inline bool operator<(const MazeFrame &rhs) const {
        return score < rhs.score;
    }

    std::vector<MazeFrame> stepToBranch(const std::vector<std::string> &,
        std::set<std::tuple<size_t, size_t, int32_t, int32_t>> &);
    std::vector<MazeFrame> branchJunction(const std::vector<std::string> &,
        std::map<std::pair<size_t, size_t>, size_t> &, const size_t);
};

class Day16 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::tuple<size_t, size_t, MazeFrame> getStartEnd(const std::vector<std::string> &lines);
};
} // namespace aoc
#endif
