
#include "solution/Day04.h"
#include <cstdint>
#include <stdexcept>

namespace aoc {

std::string Day04::part1(const std::vector<std::string> &lines) {
    size_t acc{};
    for (size_t row = 0; row < lines.size(); ++row) {
        for (size_t col = 0; col < lines.at(row).size(); ++col) {
            if ('X' == lines.at(row).at(col)) {
                for (int32_t right = -1; right <= 1; ++right) {
                    for (int32_t up = -1; up <= 1; ++up) {
                        acc += xmasSearch(lines, row, col, right, up);
                    }
                }
            }
        }
    }
    return std::to_string(acc);
}

std::string Day04::part2(const std::vector<std::string> &lines) {
    size_t acc{};

    for (size_t row = 1; row < lines.size() - 1; ++row) {
        for (size_t col = 1; col < lines.at(row).size() - 1; ++col) {
            if ('A' == lines.at(row).at(col)) {
                const char up_left = lines.at(row - 1).at(col - 1);
                const char up_right = lines.at(row - 1).at(col + 1);
                const char down_left = lines.at(row + 1).at(col - 1);
                const char down_right = lines.at(row + 1).at(col + 1);
                acc += xmasX(up_left, down_right) && xmasX(up_right, down_left);
            }
        }
    }
    return std::to_string(acc);
}

size_t Day04::xmasSearch(const std::vector<std::string> &lines, const int32_t row,
    const int32_t col, const int32_t right, const int32_t down) {

    try {
        if ('M' == lines.at(row + down).at(col + right) &&
            'A' == lines.at(row + 2 * down).at(col + 2 * right) &&
            'S' == lines.at(row + 3 * down).at(col + 3 * right)) {
            return 1;
        }
    } catch (const std::out_of_range &) {
        // ...
    }
    return 0;
}

size_t Day04::xmasX(const char c1, const char c2) {
    return ('M' == c1 && 'S' == c2) || ('S' == c1 && 'M' == c2) ? 1 : 0;
}
} // namespace aoc
