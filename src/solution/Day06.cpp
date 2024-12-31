
#include "solution/Day06.h"
#include <stdexcept>

namespace aoc {

std::string Day06::part1(const std::vector<std::string> &lines) {
    return std::to_string(walkAndRecord(lines).size() + 1);
}

std::string Day06::part2(const std::vector<std::string> &lines) {

    size_t acc{};
    std::vector<std::string> lines_cpy = lines;
    getGuardPos(lines);
    const size_t guard_row_orig = guard_row;
    const size_t guard_col_orig = guard_col;

    for (const auto &[row, col] : walkAndRecord(lines)) {
        if (guard_row_orig == row && guard_col_orig == col) {
            continue;
        }
        guard_row = guard_row_orig;
        guard_col = guard_col_orig;

        lines_cpy.at(row).at(col) = '#';
        acc += loops(lines_cpy);
        lines_cpy.at(row).at(col) = '.';
    }
    return std::to_string(acc);
}

void Day06::getGuardPos(const std::vector<std::string> &lines) {
    for (guard_row = 0; guard_row < lines.size(); ++guard_row) {
        for (guard_col = 0; guard_col < lines.at(guard_row).size(); ++guard_col) {
            if ('^' == lines.at(guard_row).at(guard_col)) {
                return;
            }
        }
    }
}

std::set<std::pair<size_t, size_t>> Day06::walkAndRecord(
    const std::vector<std::string> &lines) {

    std::set<std::pair<size_t, size_t>> ret{};
    int32_t x{0}, y{-1};
    getGuardPos(lines);
    try {
        for (;;) {
            if ('#' == lines.at(guard_row + y).at(guard_col + x)) {
                if (0 == x) {
                    x = -y;
                    y = 0;
                } else {
                    y = x;
                    x = 0;
                }
            } else {
                guard_row += y;
                guard_col += x;
                ret.emplace(guard_row, guard_col);
            }
        }
    } catch (const std::out_of_range &) {
    }

    return ret;
}

size_t Day06::loops(const std::vector<std::string> &lines) {

    std::set<std::tuple<size_t, size_t, Direction>> visited{};
    Direction dir = UP;
    int32_t x{0}, y{-1};
    try {
        for (;;) {
            if ('#' == lines.at(guard_row + y).at(guard_col + x)) {
                std::tuple<size_t, size_t, Direction> curr_pos{guard_row, guard_col, dir};
                if (visited.contains(curr_pos)) {
                    return 1;
                } else {
                    visited.insert(std::move(curr_pos));
                }
                switch (dir) {
                    case UP: dir = RIGHT; break;
                    case RIGHT: dir = DOWN; break;
                    case DOWN: dir = LEFT; break;
                    case LEFT: dir = UP; break;
                }
                if (0 == x) {
                    x = -y;
                    y = 0;
                } else {
                    y = x;
                    x = 0;
                }
            } else {
                guard_row += y;
                guard_col += x;
            }
        }
    } catch (const std::out_of_range &) {
    }
    return 0;
}
} // namespace aoc
