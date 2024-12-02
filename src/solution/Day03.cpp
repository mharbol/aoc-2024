
#include "solution/Day03.h"
#include <cstddef>
#include <string>
#include <cstddef>
#include <regex>
#include <string>

namespace aoc {

std::string Day03::part1(const std::vector<std::string> &lines) {
    size_t acc{};
    for (const auto &line : lines) {
        acc += mulLine(line);
    }
    return std::to_string(acc);
}

std::string Day03::part2(const std::vector<std::string> &lines) {
    size_t acc{};
    bool is_do{true};
    for (const auto &line : lines) {
        acc += mulLineDoDont(line, is_do);
    }
    return std::to_string(acc);
}

size_t Day03::mulLine(const std::string &line) {

    size_t acc{};
    const std::regex pattern("mul\\([0-9]{1,3},[0-9]{1,3}\\)");

    const auto start = std::sregex_iterator(line.begin(), line.end(), pattern);
    const auto end = std::sregex_iterator();

    for (auto iter = start; iter != end; ++iter) {
        const auto &mul = iter->str();
        const size_t comma_pos = mul.find(',');
        acc += std::stoi(mul.substr(4, comma_pos - 4)) *
               std::stoi(mul.substr(comma_pos + 1, mul.size() - comma_pos));
    }
    return acc;
}

size_t Day03::mulLineDoDont(const std::string &line, bool &is_do) {

    size_t acc{};
    const std::regex pattern("(mul\\([0-9]{1,3},[0-9]{1,3}\\))|(do\\(\\))|(don't\\(\\))");

    const auto start = std::sregex_iterator(line.begin(), line.end(), pattern);
    const auto end = std::sregex_iterator();

    for (auto iter = start; iter != end; ++iter) {
        const auto &mul = iter->str();
        if ("do()" == mul) {
            is_do = true;
        } else if ("don't()" == mul) {
            is_do = false;
        } else if (is_do) {
            const size_t comma_pos = mul.find(',');
            acc += std::stoi(mul.substr(4, comma_pos - 4)) *
                   std::stoi(mul.substr(comma_pos + 1, mul.size() - comma_pos));
        }
    }
    return acc;
}
} // namespace aoc
