
#include "solution/Day01.h"
#include <algorithm>
#include <unordered_map>
#include <string>

namespace aoc {

std::string Day01::part1(const std::vector<std::string> &lines) {
    std::vector<int32_t> left{};
    std::vector<int32_t> right{};
    for (const auto &line : lines) {
        left.push_back(std::stoi(line.substr(0, 5)));
        right.push_back(std::stoi(line.substr(8, 5)));
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    size_t acc{};
    auto iter_r = right.begin();
    auto iter_l = left.begin();
    const auto end = right.cend();
    while (end != iter_r) {
        acc += std::abs(*iter_r++ - *iter_l++);
    }
    return std::to_string(acc);
}

std::string Day01::part2(const std::vector<std::string> &lines) {
    std::vector<int32_t> left{};
    std::unordered_map<int32_t, size_t> right_count{};
    for (const auto &line : lines) {
        left.push_back(std::stoi(line.substr(0, 5)));
        right_count[std::stoi(line.substr(8, 5))]++;
    }
    size_t acc{};
    for (const auto num : left) {
        acc += right_count[num] * num;
    }
    return std::to_string(acc);
}
} // namespace aoc
