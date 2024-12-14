
#include "solution/Day12.h"
#include <utility>

namespace aoc {

std::string Day12::part1(const std::vector<std::string> &lines) {

    ROW_MAX = lines.size();
    COL_MAX = lines.at(0).size();

    size_t acc{};
    std::vector<std::vector<bool>> visted(ROW_MAX, std::vector<bool>(COL_MAX, false));

    for (int32_t row = 0; row < ROW_MAX; ++row) {
        for (int32_t col = 0; col < COL_MAX; ++col) {
            if (!visted.at(row).at(col)) {
                auto [area, perimeter] =
                    floodFillRegion(row, col, visted, lines, lines.at(row).at(col));
                acc += area * perimeter;
            }
        }
    }
    return std::to_string(acc);
}

std::string Day12::part2(const std::vector<std::string> &lines) {

    ROW_MAX = lines.size();
    COL_MAX = lines.at(0).size();
    size_t acc{};

    std::vector<std::vector<bool>> visted(ROW_MAX, std::vector<bool>(COL_MAX, false));
    std::set<std::tuple<int32_t, int32_t, Direction>> visited_edges{};

    for (int32_t row = 0; row < ROW_MAX; ++row) {
        for (int32_t col = 0; col < COL_MAX; ++col) {
            if (!visted.at(row).at(col)) {
                auto [area, sides] = floodFillSides(row, col, visted, lines,
                    lines.at(row).at(col), visited_edges);

                acc += area * sides;
            }
        }
    }
    return std::to_string(acc);
}

std::pair<size_t, size_t> Day12::floodFillRegion(const int32_t row, const int32_t col,
    std::vector<std::vector<bool>> &visited, const std::vector<std::string> &lines,
    const char id) {

    if (0 > row || 0 > col || ROW_MAX <= row || COL_MAX <= col || visited.at(row).at(col) ||
        id != lines.at(row).at(col)) {
        return {0, 0};
    }
    visited.at(row).at(col) = true;
    size_t area = 1;
    size_t perimeter{};

    for (auto [x, y] :
        std::vector<std::pair<int32_t, int32_t>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
        auto reg = floodFillRegion(row + x, col + y, visited, lines, id);
        area += reg.first;
        perimeter += checkNeighborId(row + x, col + y, id, lines);
        perimeter += reg.second;
    }
    return {area, perimeter};
}

std::pair<size_t, size_t> Day12::floodFillSides(const int32_t row, const int32_t col,
    std::vector<std::vector<bool>> &visited, const std::vector<std::string> &lines,
    const char id, std::set<std::tuple<int32_t, int32_t, Direction>> &visited_edges) {

    if (0 > row || 0 > col || ROW_MAX <= row || COL_MAX <= col || visited.at(row).at(col) ||
        id != lines.at(row).at(col)) {
        return {0, 0};
    }
    visited.at(row).at(col) = true;

    size_t area = 1;
    size_t sides = checkSides(row, col, id, lines, visited_edges);

    for (auto [x, y] :
        std::vector<std::pair<int32_t, int32_t>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
        auto reg = floodFillSides(row + x, col + y, visited, lines, id, visited_edges);
        area += reg.first;
        sides += reg.second;
    }
    return {area, sides};
}

size_t Day12::checkNeighborId(int32_t row, int32_t col, char id,
    const std::vector<std::string> &lines) {

    if (0 > row || 0 > col || ROW_MAX <= row || COL_MAX <= col ||
        id != lines.at(row).at(col)) {
        return 1;
    }
    return 0;
}

size_t Day12::checkSides(const int32_t row, const int32_t col, const char id,
    const std::vector<std::string> &lines,
    std::set<std::tuple<int32_t, int32_t, Direction>> &visited_edges) {

    size_t tot{};
    std::tuple<int32_t, int32_t, Direction> tup{};

    // check down row
    tup = std::make_tuple(row, col, DOWN);
    if (!visited_edges.contains(tup) && isSide(row, col, id, DOWN, lines)) {
        ++tot;
        for (int32_t c = col; isSide(row, c, id, DOWN, lines); --c) {
            visited_edges.insert(std::make_tuple(row, c, DOWN));
        }
        for (int32_t c = col + 1; isSide(row, c, id, DOWN, lines); ++c) {
            visited_edges.insert(std::make_tuple(row, c, DOWN));
        }
    }

    // check up row
    tup = std::make_tuple(row, col, UP);
    if (!visited_edges.contains(tup) && isSide(row, col, id, UP, lines)) {
        ++tot;
        for (int32_t c = col; isSide(row, c, id, UP, lines); --c) {
            visited_edges.insert(std::make_tuple(row, c, UP));
        }
        for (int32_t c = col + 1; isSide(row, c, id, UP, lines); ++c) {
            visited_edges.insert(std::make_tuple(row, c, UP));
        }
    }

    // check left row
    tup = std::make_tuple(row, col, LEFT);
    if (!visited_edges.contains(tup) && isSide(row, col, id, LEFT, lines)) {
        ++tot;
        for (int32_t r = row; isSide(r, col, id, LEFT, lines); --r) {
            visited_edges.insert(std::make_tuple(r, col, LEFT));
        }
        for (int32_t r = row + 1; isSide(r, col, id, LEFT, lines); ++r) {
            visited_edges.insert(std::make_tuple(r, col, LEFT));
        }
    }

    // check left row
    tup = std::make_tuple(row, col, RIGHT);
    if (!visited_edges.contains(tup) && isSide(row, col, id, RIGHT, lines)) {
        ++tot;
        for (int32_t r = row; isSide(r, col, id, RIGHT, lines); --r) {
            visited_edges.insert(std::make_tuple(r, col, RIGHT));
        }
        for (int32_t r = row + 1; isSide(r, col, id, RIGHT, lines); ++r) {
            visited_edges.insert(std::make_tuple(r, col, RIGHT));
        }
    }

    return tot;
}

bool Day12::isSide(int32_t row, int32_t col, const char id, Direction dir,
    const std::vector<std::string> &lines) {

    if (0 > row || 0 > col || ROW_MAX <= row || COL_MAX <= col ||
        lines.at(row).at(col) != id) {
        return false;
    }

    switch (dir) {
        case DOWN: return ROW_MAX - 1 == row || id != lines.at(row + 1).at(col);
        case UP: return 0 == row || id != lines.at(row - 1).at(col);
        case RIGHT: return COL_MAX - 1 == col || id != lines.at(row).at(col + 1);
        case LEFT: return 0 == col || id != lines.at(row).at(col - 1);
    }
    return false;
}
} // namespace aoc
