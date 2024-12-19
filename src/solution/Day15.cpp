
#include "solution/Day15.h"

namespace aoc {

std::string Day15::part1(const std::vector<std::string> &lines) {
    auto [warehouse, moves] = parse(lines);
    for (const auto &line : moves) {
        for (const char move : line) {
            warehouse.pushBox(move);
        }
    }
    return std::to_string(warehouse.sumGPS('O'));
}

std::string Day15::part2(const std::vector<std::string> &lines) {
    auto [warehouse, moves] = parseWide(lines);
    for (const auto &line : moves) {
        for (const char move : line) {
            warehouse.pushWideBox(move);
        }
    }
    return std::to_string(warehouse.sumGPS('['));
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

std::pair<LanternfishWarehouse, std::vector<std::string>> Day15::parseWide(
    const std::vector<std::string> &lines) {

    std::vector<std::string> warehouse{};
    std::vector<std::string> moves{};
    std::string line{};
    auto iter = lines.begin();
    while (!iter->empty()) {
        for (const char ch : *iter) {
            switch (ch) {
                case '.': line.append(".."); break;
                case '#': line.append("##"); break;
                case '@': line.append("@."); break;
                case 'O': line.append("[]"); break;
            }
        }
        warehouse.push_back(std::move(line));
        line.clear();
        ++iter;
    }
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

void LanternfishWarehouse::pushWideBox(const char dir) {
    int32_t delta{};
    switch (dir) {
        case '^':
        case '<': delta = -1; break;
        case 'v':
        case '>': delta = 1; break;
    }
    if ('<' == dir || '>' == dir) {
        if (canPushWideHorz(robo_row, robo_col + delta, delta)) {
            pushWideHorz(robo_row, robo_col + delta, delta);
            warehouse.at(robo_row).at(robo_col) = '.';
            warehouse.at(robo_row).at(robo_col += delta) = '@';
        }
    } else if (canPushWideVert(robo_row + delta, robo_col, delta)) {
        pushWideVert(robo_row + delta, robo_col, delta);
        warehouse.at(robo_row).at(robo_col) = '.';
        warehouse.at(robo_row += delta).at(robo_col) = '@';
    }
}

bool LanternfishWarehouse::canPushWideHorz(const size_t row, const size_t col,
    const int32_t dc) {

    switch (warehouse.at(row).at(col)) {
        case '.': return true;
        case '#': return false;
        default: return canPushWideHorz(row, col + dc, dc);
    }
}

bool LanternfishWarehouse::canPushWideVert(const size_t row, const size_t col,
    const int32_t dr) {

    switch (warehouse.at(row).at(col)) {
        case '.': return true;
        case '[':
            return canPushWideVert(row + dr, col, dr) &&
                   canPushWideVert(row + dr, col + 1, dr);
        case ']':
            return canPushWideVert(row + dr, col, dr) &&
                   canPushWideVert(row + dr, col - 1, dr);
        default: return false;
    }
}

void LanternfishWarehouse::pushWideHorz(const size_t row, size_t col, const int32_t dc) {

    while ('.' != warehouse.at(row).at(col)) {
        if ('[' == warehouse.at(row).at(col)) {
            warehouse.at(row).at(col) = ']';
        } else {
            warehouse.at(row).at(col) = '[';
        }
        col += dc;
    }
    if ('[' == warehouse.at(row).at(col - dc)) {
        warehouse.at(row).at(col) = ']';
    } else {
        warehouse.at(row).at(col) = '[';
    }
}

void LanternfishWarehouse::pushWideVert(const size_t row, const size_t col, const int32_t dr) {

    switch (warehouse.at(row).at(col)) {
        case '.':
            warehouse.at(row).at(col) = warehouse.at(row - dr).at(col);
            warehouse.at(row - dr).at(col) = '.';
            break;
        case '[':
            pushWideVert(row + dr, col, dr);
            pushWideVert(row, col + 1, dr);
            break;
        case ']':
            pushWideVert(row + dr, col, dr);
            pushWideVert(row, col - 1, dr);
            break;
    }
}

size_t LanternfishWarehouse::sumGPS(const char box) {
    size_t ret{};
    for (size_t row = 0; row < height; ++row) {
        for (size_t col = 0; col < width; ++col) {
            if (box == warehouse.at(row).at(col)) {
                ret += 100 * row + col;
            }
        }
    }
    return ret;
}
} // namespace aoc
