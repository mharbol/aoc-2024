
#include "solution/Day18.h"
#include <queue>

namespace aoc {

std::string Day18::part1(const std::vector<std::string> &lines) {
    const auto mem_grid = parseKb(1024, lines);
    const MemNode start(0, 0, 0);
    return std::to_string(MemNode::aStarKb(start, mem_grid));
}

std::string Day18::part2(const std::vector<std::string> &lines) {
    return lines.at(getKillerByteIdx(lines) - 1);
}

size_t Day18::getKillerByteIdx(const std::vector<std::string> &lines) {

    size_t left = 1024;
    size_t right = lines.size() - 1;
    size_t mid{};
    while (left < right) {
        mid = (left + right) / 2;
        const auto mem_grid = parseKb(mid, lines);
        const MemNode start(0, 0, 0);
        if (0 != MemNode::aStarKb(start, mem_grid)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return mid;
}

std::set<std::pair<size_t, size_t>> Day18::parseKb(const size_t num_lines,
    const std::vector<std::string> &lines) {

    std::set<std::pair<size_t, size_t>> ret{};
    auto iter = lines.begin();
    const auto end = iter + num_lines;
    while (iter != end) {
        const size_t comma_pos = iter->find(',');
        const size_t col = std::stoul(iter->substr(0, comma_pos));
        const size_t row = std::stoul(iter->substr(comma_pos + 1));
        ret.emplace(row, col);
        ++iter;
    }
    return ret;
}

size_t MemNode::aStarKb(const MemNode &start,
    const std::set<std::pair<size_t, size_t>> &mem_grid) {

    std::priority_queue<MemNode, std::vector<MemNode>, std::greater<MemNode>> pq{};
    std::set<std::pair<size_t, size_t>> visited{};

    pq.push(start);

    while (!pq.empty()) {
        auto curr = pq.top();
        pq.pop();
        if (curr.isDestination()) {
            return curr.g_cost;
        }
        visited.emplace(curr.row, curr.col);
        for (const auto &neighbor : curr.getNeighbors()) {
            if (!neighbor.isValid(mem_grid)) {
                continue;
            } else if (!visited.contains({neighbor.row, neighbor.col})) {
                pq.push(neighbor);
            }
        }
    }
    return 0;
}

std::vector<MemNode> MemNode::getNeighbors() const {

    std::vector<MemNode> ret{};
    if (0 < row) {
        ret.emplace_back(row - 1, col, g_cost + 1);
    }
    if (0 < col) {
        ret.emplace_back(row, col - 1, g_cost + 1);
    }
    if (RC_MAX > row) {
        ret.emplace_back(row + 1, col, g_cost + 1);
    }
    if (RC_MAX > col) {
        ret.emplace_back(row, col + 1, g_cost + 1);
    }
    return ret;
}

bool MemNode::isValid(const std::set<std::pair<size_t, size_t>> &mem_grid) const {
    return (row <= RC_MAX && col <= RC_MAX && !mem_grid.contains({row, col}));
}

bool MemNode::isDestination() const {
    return row == RC_MAX && col == RC_MAX;
}

size_t MemNode::calcH() const {
    return RC_MAX - row + RC_MAX - col;
}

size_t MemNode::calcF() const {
    return calcH() + g_cost;
}

inline bool operator<(const aoc::MemNode &lhs, const aoc::MemNode &rhs) {
    return lhs.calcF() < rhs.calcF();
}
inline bool operator>(const aoc::MemNode &lhs, const aoc::MemNode &rhs) {
    return rhs.calcF() < lhs.calcF();
}
inline bool operator==(const aoc::MemNode &lhs, const aoc::MemNode &rhs) {
    return lhs.row == rhs.row && lhs.col == rhs.col;
}
} // namespace aoc
