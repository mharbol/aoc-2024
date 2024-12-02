
#include "solution/Day02.h"
#include <sstream>
#include <string>
#include <vector>

namespace aoc {

std::string Day02::part1(const std::vector<std::string> &lines) {
    size_t acc{};
    for (const auto &line : lines) {
        acc += isSafe(line) ? 1 : 0;
    }
    return std::to_string(acc);
}

std::string Day02::part2(const std::vector<std::string> &lines) {
    size_t acc{};
    for (const auto &line : lines) {
        acc += isDampenSafe(line) ? 1 : 0;
    }
    return std::to_string(acc);
}

bool Day02::isSafe(const std::string &report) {

    std::vector<int32_t> levels{};
    std::stringstream str(report);
    std::string level{};
    while (std::getline(str, level, ' ')) {
        levels.push_back(std::stoi(level));
    }

    std::vector<int32_t> diffs{};
    auto iter = levels.begin();
    int32_t curr = *iter++;

    while (iter != levels.end()) {
        diffs.push_back(curr - *iter);
        curr = *iter++;
    }

    const bool increasing = diffs.at(0) > 0;
    for (const auto diff : diffs) {
        if (0 == diff || std::abs(diff) > 3 || (increasing && diff < 0) ||
            (!increasing && diff > 0)) {
            return false;
        }
    }
    return true;
}

bool Day02::isDampenSafe(const std::string &report) {
    if (isSafe(report)) {
        return true;
    }
    std::vector<int32_t> levels{};
    std::stringstream str(report);
    std::string level{};
    while (std::getline(str, level, ' ')) {
        levels.push_back(std::stoi(level));
    }

    for (size_t drop_idx = 0; drop_idx < levels.size(); ++drop_idx) {
        std::stringstream report_str{};
        for (size_t idx = 0; idx < levels.size(); ++idx) {
            if (idx != drop_idx) {
                report_str << levels.at(idx) << " ";
            }
        }
        if (isSafe(report_str.str())) {
            return true;
        }
    }
    return false;
}
} // namespace aoc
