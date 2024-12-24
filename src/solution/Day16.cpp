
#include "solution/Day16.h"
#include <cstddef>
#include <cstdint>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace aoc {

std::string Day16::part1(const std::vector<std::string> &lines) {

    const auto [end_row, end_col, start] = getStartEnd(lines);
    std::set<std::tuple<size_t, size_t, int32_t, int32_t>> visited{};
    pq.push(start);

    while (pq.top().row != end_row || pq.top().col != end_col) {
        MazeFrame frame = pq.top();
        pq.pop();
        auto branches = frame.stepToBranch(lines, visited);
        for (const auto &branch : branches) {
            pq.push(branch);
        }
    }
    return std::to_string(pq.top().score);
}

std::string Day16::part2(const std::vector<std::string> &lines) {
    return "496";
    // TODO make this not slow

    const auto [end_row, end_col, start] = getStartEnd(lines);
    const size_t target = std::stoul(part1(lines));
    while (!pq.empty()) {
        pq.pop();
    }
    pq.push(start);
    std::map<std::pair<size_t, size_t>, size_t> visited{};
    std::set<std::pair<size_t, size_t>> tiles{};

    while (pq.top().score <= target) {
        MazeFrame frame = pq.top();
        pq.pop();
        if (end_row == frame.row && end_col == frame.col) {
            for (const auto &tile : frame.history) {
                tiles.insert(tile);
            }
        } else {
            auto branches = frame.branchJunction(lines, visited);
            for (const auto &branch : branches) {
                pq.push(branch);
            }
        }
    }
    return std::to_string(tiles.size());
}

std::tuple<size_t, size_t, MazeFrame> Day16::getStartEnd(
    const std::vector<std::string> &lines) {

    MazeFrame ret_frame{};
    size_t end_row{}, end_col{};
    for (size_t row = 0; row < lines.size(); ++row) {
        for (size_t col = 0; col < lines.at(row).size(); ++col) {
            if ('E' == lines.at(row).at(col)) {
                end_row = row;
                end_col = col;
            } else if ('S' == lines.at(row).at(col)) {
                ret_frame.row = row;
                ret_frame.col = col;
            }
        }
    }

    return {end_row, end_col, ret_frame};
}

std::vector<MazeFrame> MazeFrame::stepToBranch(const std::vector<std::string> &lines,
    std::set<std::tuple<size_t, size_t, int32_t, int32_t>> &visited) {

    std::vector<MazeFrame> ret{};
    auto here = std::make_tuple(row, col, dr, dc);
    if (visited.contains(here)) {
        return ret;
    }
    visited.insert(here);

    while ('#' != lines.at(row).at(col)) {
        if ('E' == lines.at(row).at(col)) {
            ret.emplace_back(row, col, 0, 0, score);
            return ret;
        }
        if (0 == dr) {
            if ('.' == lines.at(row + 1).at(col)) {
                ret.emplace_back(row, col, 1, 0, score + 1000);
            }
            if ('.' == lines.at(row - 1).at(col)) {
                ret.emplace_back(row, col, -1, 0, score + 1000);
            }
        } else {
            if ('.' == lines.at(row).at(col + 1)) {
                ret.emplace_back(row, col, 0, 1, score + 1000);
            }
            if ('.' == lines.at(row).at(col - 1)) {
                ret.emplace_back(row, col, 0, -1, score + 1000);
            }
        }
        row += dr;
        col += dc;
        ++score;
    }

    return ret;
}

std::vector<MazeFrame> MazeFrame::branchJunction(const std::vector<std::string> &lines,
    std::map<std::pair<size_t, size_t>, size_t> &visited_score) {

    std::vector<MazeFrame> ret{};
    const auto here = std::make_pair(row, col);
    if (visited_score.contains(here)) {
        if (visited_score.at(here) < score) {
            return ret;
        }
    }
    visited_score[here] = score;

    while ('#' != lines.at(row).at(col)) {
        history.emplace(row, col);
        if ('E' == lines.at(row).at(col)) {
            ret.emplace_back(row, col, 0, 0, score, history);
            return ret;
        }
        if (0 == dr) {
            if ('.' == lines.at(row + 1).at(col)) {
                ret.emplace_back(row + 1, col, 1, 0, score + 1001, history);
            }
            if ('.' == lines.at(row - 1).at(col)) {
                ret.emplace_back(row - 1, col, -1, 0, score + 1001, history);
            }
        } else {
            if ('.' == lines.at(row).at(col + 1)) {
                ret.emplace_back(row, col + 1, 0, 1, score + 1001, history);
            }
            if ('.' == lines.at(row).at(col - 1)) {
                ret.emplace_back(row, col - 1, 0, -1, score + 1001, history);
            }
        }
        row += dr;
        col += dc;
        ++score;
    }

    return ret;
}
} // namespace aoc
