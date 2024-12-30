
#include "solution/Day20.h"

namespace aoc {

std::string Day20::part1(const std::vector<std::string> &lines) {
    const auto [start_row, start_col, end_row, end_col] = getStartEnd(lines);
    const auto path = getPath(lines, start_row, start_col, end_row, end_col);
    return std::to_string(countReductions(path, 2, 100));
}

std::string Day20::part2(const std::vector<std::string> &lines) {
    const auto [start_row, start_col, end_row, end_col] = getStartEnd(lines);
    const auto path = getPath(lines, start_row, start_col, end_row, end_col);
    return std::to_string(countReductions(path, 20, 100));
}

std::vector<std::pair<int32_t, int32_t>> Day20::getPath(std::vector<std::string> lines,
    int32_t row, int32_t col, const int32_t end_row, const int32_t end_col) const {

    lines.at(row).at(col) = '.';
    lines.at(end_row).at(end_col) = '.';

    std::vector<std::pair<int32_t, int32_t>> ret{};
    ret.emplace_back(row, col);
    int32_t prev_row = row;
    int32_t prev_col = col;

    while (end_row != row || end_col != col) {
        if (0 < row && '.' == lines.at(row - 1).at(col) && prev_row != row - 1) {
            prev_col = col;
            prev_row = row--;
        } else if (static_cast<size_t>(row + 1) < lines.size() &&
                   '.' == lines.at(row + 1).at(col) && prev_row != row + 1) {
            prev_col = col;
            prev_row = row++;
        } else if (0 < col && '.' == lines.at(row).at(col - 1) && col - 1 != prev_col) {
            prev_row = row;
            prev_col = col--;
        } else {
            prev_row = row;
            prev_col = col++;
        }
        ret.emplace_back(row, col);
    }
    return ret;
}

size_t Day20::countReductions(const std::vector<std::pair<int32_t, int32_t>> &points,
    const int32_t cheat_threshold, const int32_t target) const {

    size_t acc{};
    for (size_t idx = 0; idx < points.size() - target; ++idx) {
        for (size_t dest_idx = idx + target; dest_idx < points.size(); ++dest_idx) {
            const int32_t row = points.at(idx).first;
            const int32_t col = points.at(idx).second;
            const int32_t dest_row = points.at(dest_idx).first;
            const int32_t dest_col = points.at(dest_idx).second;
            const int32_t row_dist = std::abs(row - dest_row);
            const int32_t col_dist = std::abs(col - dest_col);
            const int32_t cheat_time = dest_idx - idx;      // distance would have travelled
            const int32_t cheat_dist = row_dist + col_dist; // distance actually travelled

            if (cheat_threshold >= cheat_dist && target <= cheat_time - cheat_dist) {
                ++acc;
            }
        }
    }
    return acc;
}

std::tuple<int32_t, int32_t, int32_t, int32_t> Day20::getStartEnd(
    const std::vector<std::string> &lines) const {

    std::tuple<int32_t, int32_t, int32_t, int32_t> ret{};
    for (size_t row = 0; row < lines.size(); ++row) {
        for (size_t col = 0; col < lines.at(row).size(); ++col) {
            if ('S' == lines.at(row).at(col)) {
                std::get<0>(ret) = row;
                std::get<1>(ret) = col;
            } else if ('E' == lines.at(row).at(col)) {
                std::get<2>(ret) = row;
                std::get<3>(ret) = col;
            }
        }
    }
    return ret;
}
} // namespace aoc
