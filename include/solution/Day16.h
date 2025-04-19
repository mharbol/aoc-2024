
#ifndef __AOC_DAY_16_H__
#define __AOC_DAY_16_H__

#include "Solution.h"
#include <map>
#include <queue>
#include <set>
#include <unordered_set>

namespace aoc {
struct MazeFrame {
    size_t row{};
    size_t col{};
    int32_t dr = 0;
    int32_t dc = 1;
    size_t score = 0;
    size_t frame_id = 0;
    size_t parent_id = 0;

    MazeFrame() = default;

    MazeFrame(size_t row, size_t col, int32_t dr, int32_t dc, size_t score)
        : row(row), col(col), dr(dr), dc(dc), score(score) {}

    MazeFrame(size_t row, size_t col, int32_t dr, int32_t dc, size_t score, size_t frame_id,
        size_t parent_id)
        : row(row), col(col), dr(dr), dc(dc), score(score), frame_id(frame_id),
          parent_id(parent_id) {}

    void stepToBranch(const std::vector<std::string> &lines,
        std::unordered_set<std::tuple<size_t, size_t, int32_t, int32_t>> &visited,
        std::priority_queue<MazeFrame, std::vector<MazeFrame>, std::greater<MazeFrame>> &pq);

    void branchJunction(const std::vector<std::string> &lines,
        std::map<std::pair<size_t, size_t>, size_t> &visited_scores,
        std::map<size_t, std::set<std::pair<size_t, size_t>>> &frame_history,
        std::map<size_t, size_t> &frame_parent_assoc,
        std::priority_queue<MazeFrame, std::vector<MazeFrame>, std::greater<MazeFrame>> &pq,
        const size_t target, size_t &new_frame_id);

    inline bool operator<(const MazeFrame &rhs) const {
        return score < rhs.score;
    }
    inline bool operator>(const MazeFrame &rhs) const {
        return score > rhs.score;
    }
};

class Day16 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::tuple<size_t, size_t, MazeFrame> getStartEnd(const std::vector<std::string> &lines);
    size_t lowestReindeer(const std::vector<std::string> &lines);
};
} // namespace aoc

namespace std {
template <>
struct hash<std::tuple<size_t, size_t, int32_t, int32_t>> {
    size_t operator()(const std::tuple<size_t, size_t, int32_t, int32_t> &frame) const {
        return ((std::get<0>(frame) * 37 + std::get<1>(frame)) * 37 +
                   static_cast<size_t>(std::get<2>(frame))) *
                   37 +
               static_cast<size_t>(std::get<3>(frame));
    }
};
} // namespace std
#endif
