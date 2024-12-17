
#include "solution/Day15.h"
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace aoc {

std::string Day15::part1(const std::vector<std::string> &lines) {
    auto [warehouse, moves] = parse(lines);
    for (const auto &line : moves) {
        for (const char move : line) {
            warehouse.pushBox(move);
        }
    }
    return std::to_string(warehouse.sumGPS());
}

std::string Day15::part2(const std::vector<std::string> &) {
    return "";
}

std::pair<LanternfishWarehouse, std::vector<std::string>> Day15::parse(
    const std::vector<std::string> &lines) {

    std::vector<std::string> warehouse{};
    std::vector<std::string> moves{};
    auto iter = lines.begin();
    while (!iter->empty()) {
        ++iter;
    }
    warehouse.insert(warehouse.end(), lines.begin(), iter);
    moves.insert(moves.end(), ++iter, lines.end());
    return {LanternfishWarehouse(std::move(warehouse)), std::move(moves)};
}

LanternfishWarehouse::LanternfishWarehouse(std::vector<std::string> &&warehouse)
    : warehouse(warehouse), width(warehouse.at(0).size()), height(warehouse.size()) {
    for (robo_row = 0; robo_row < height; ++robo_row) {
        for (robo_col = 0; robo_col < width; ++robo_col) {
            if ('@' == warehouse.at(robo_row).at(robo_col)) {
                return;
            }
        }
    }
}

void LanternfishWarehouse::pushBox(const char dir) {
    int32_t dr{}, dc{};
    switch (dir) {
        case '^': dr = -1; break;
        case 'v': dr = 1; break;
        case '>': dc = 1; break;
        case '<': dc = -1; break;
    }
    if ('.' != warehouse.at(robo_row + dr).at(robo_col + dc)) {

        int32_t row = robo_row;
        int32_t col = robo_col;
        do {
            row += dr;
            col += dc;
        } while ('O' == warehouse.at(row).at(col));

        if ('.' == warehouse.at(row).at(col)) {
            warehouse.at(row).at(col) = 'O';
        } else {
            return;
        }
    }
    warehouse.at(robo_row).at(robo_col) = '.';
    warehouse.at(robo_row += dr).at(robo_col += dc) = '@';
}

size_t LanternfishWarehouse::sumGPS() {
    size_t ret{};
    for (size_t row = 0; row < height; ++row) {
        for (size_t col = 0; col < width; ++col) {
            if ('O' == warehouse.at(row).at(col)) {
                ret += 100 * row + col;
            }
        }
    }
    return ret;
}
} // namespace aoc
