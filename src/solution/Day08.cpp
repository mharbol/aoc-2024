
#include "solution/Day08.h"
#include <numeric>
#include <set>

namespace aoc {

std::string Day08::part1(const std::vector<std::string> &lines) {

    const int32_t MAX_ROW{static_cast<int32_t>(lines.size())};
    const int32_t MAX_COL{static_cast<int32_t>(lines.at(0).size())};

    std::set<std::pair<int32_t, int32_t>> count_ans{};
    const auto antennas = getAntennas(lines);

    for (const auto &antenna_locs : antennas) {
        const auto &antenna_coords = antenna_locs.second;
        if (2 > antenna_coords.size()) {
            continue;
        }

        for (size_t i = 0; i < antenna_coords.size() - 1; ++i) {
            for (size_t j = i + 1; j < antenna_coords.size(); ++j) {
                const auto [r1, c1] = antenna_coords.at(i);
                const auto [r2, c2] = antenna_coords.at(j);
                const int32_t dr = r2 - r1;
                const int32_t dc = c2 - c1;
                const int32_t an1r = r1 - dr;
                const int32_t an1c = c1 - dc;
                const int32_t an2r = r2 + dr;
                const int32_t an2c = c2 + dc;
                if (0 <= an1r && 0 <= an1c && MAX_ROW > an1r && MAX_COL > an1c) {
                    count_ans.emplace(an1r, an1c);
                }
                if (0 <= an2c && MAX_ROW > an2r && MAX_COL > an2c) {
                    count_ans.emplace(an2r, an2c);
                }
            }
        }
    }
    return std::to_string(count_ans.size());
}

std::string Day08::part2(const std::vector<std::string> &lines) {

    const int32_t MAX_ROW{static_cast<int32_t>(lines.size())};
    const int32_t MAX_COL{static_cast<int32_t>(lines.at(0).size())};

    std::set<std::pair<int32_t, int32_t>> count_ans{};
    const auto antennas = getAntennas(lines);

    for (const auto &antenna_locs : antennas) {
        const auto &antenna_coords = antenna_locs.second;
        if (2 > antenna_coords.size()) {
            continue;
        }
        for (size_t i = 0; i < antenna_coords.size() - 1; ++i) {
            for (size_t j = i + 1; j < antenna_coords.size(); ++j) {
                auto [r1, c1] = antenna_coords.at(i);
                auto [r2, c2] = antenna_coords.at(j);
                int32_t dr = r2 - r1;
                int32_t dc = c2 - c1;
                int32_t gcd = std::gcd(dr, std::abs(dc));
                dr /= gcd;
                dc /= gcd;
                while (0 <= r1 && 0 <= c1 && MAX_ROW > r1 && MAX_COL > c1) {
                    count_ans.emplace(r1, c1);
                    r1 -= dr;
                    c1 -= dc;
                }
                while (0 <= c2 && MAX_ROW > r2 && MAX_COL > c2) {
                    count_ans.emplace(r2, c2);
                    r2 += dr;
                    c2 += dc;
                }
            }
        }
    }
    return std::to_string(count_ans.size());
}

std::map<char, std::vector<std::pair<int32_t, int32_t>>> Day08::getAntennas(
    const std::vector<std::string> &lines) {

    std::map<char, std::vector<std::pair<int32_t, int32_t>>> ret{};
    for (size_t row = 0; row < lines.size(); ++row) {
        for (size_t col = 0; col < lines.at(row).size(); ++col) {
            if (char ch = lines.at(row).at(col); '.' != ch) {
                ret[ch].emplace_back(row, col);
            }
        }
    }
    return ret;
}
} // namespace aoc
