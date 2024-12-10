
#include "solution/Day10.h"

namespace aoc {

std::string Day10::part1(const std::vector<std::string> &lines) {

    size_t acc{};
    for (size_t row = 0; row < lines.size(); ++row) {
        for (size_t col = 0; col < lines.at(row).size(); ++col) {
            if ('0' == lines.at(row).at(col)) {
                acc += trailScore(lines, row, col, '0').size();
            }
        }
    }
    return std::to_string(acc);
}

std::string Day10::part2(const std::vector<std::string> &lines) {
    size_t acc{};
    for (size_t row = 0; row < lines.size(); ++row) {
        for (size_t col = 0; col < lines.at(row).size(); ++col) {
            if ('0' == lines.at(row).at(col)) {
                acc += distinctTrails(lines, row, col, '0');
            }
        }
    }
    return std::to_string(acc);
}
std::set<std::pair<int32_t, int32_t>> Day10::trailScore(const std::vector<std::string> &lines,
    const int32_t row, const int32_t col, const char target) {

    std::set<std::pair<int32_t, int32_t>> ret{};

    if (0 > row || 0 > col || static_cast<int32_t>(lines.size()) <= row ||
        static_cast<int32_t>(lines.at(row).size()) <= col) {
        return ret;
    }

    if ('9' == target && lines.at(row).at(col) == target) {
        ret.emplace(row, col);
        return ret;
    }

    if (lines.at(row).at(col) == target) {
        auto up = trailScore(lines, row - 1, col, target + 1);
        auto down = trailScore(lines, row + 1, col, target + 1);
        auto left = trailScore(lines, row, col - 1, target + 1);
        auto right = trailScore(lines, row, col + 1, target + 1);
        ret.insert(up.cbegin(), up.cend());
        ret.insert(down.cbegin(), down.cend());
        ret.insert(left.cbegin(), left.cend());
        ret.insert(right.cbegin(), right.cend());
    }

    return ret;
}

size_t Day10::distinctTrails(const std::vector<std::string> &lines, const int32_t row,
    const int32_t col, const char target) {

    if (0 > row || 0 > col || static_cast<int32_t>(lines.size()) <= row ||
        static_cast<int32_t>(lines.at(row).size()) <= col) {
        return 0;
    }

    if ('9' == target && lines.at(row).at(col) == target) {
        return 1;
    }

    if (lines.at(row).at(col) == target) {
        return distinctTrails(lines, row - 1, col, target + 1) +
               distinctTrails(lines, row + 1, col, target + 1) +
               distinctTrails(lines, row, col - 1, target + 1) +
               distinctTrails(lines, row, col + 1, target + 1);
    }
    return 0;
}
} // namespace aoc
