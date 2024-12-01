
#include "solution/Day01.h"
#include <algorithm>
#include <map>
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
    for (size_t idx = 0; idx < left.size(); ++idx) {
        acc += std::abs(left.at(idx) - right.at(idx));
    }
    return std::to_string(acc);
}

std::string Day01::part2(const std::vector<std::string> &lines) {
    std::vector<int32_t> left{};
    std::vector<int32_t> right{};
    for (const auto &line : lines) {
        left.push_back(std::stoi(line.substr(0, 5)));
        right.push_back(std::stoi(line.substr(8, 5)));
    }
    std::map<int32_t, size_t> right_count{};
    for (const auto num : right) {
        right_count[num]++;
    }
    size_t acc{};
    for (const auto num : left) {
        acc += right_count[num] * num;
    }
    return std::to_string(acc);
}
} // namespace aoc
