
#include "solution/Day07.h"
#include <cstddef>
#include <sstream>

namespace aoc {

std::string Day07::part1(const std::vector<std::string> &lines) {
    size_t acc{};
    size_t target{};
    std::vector<size_t> nums{};
    for (const auto &line : lines) {
        parse(line, target, nums);
        acc += calibrationResult(target, nums.at(0), nums, 0) ? target : 0;
    }
    return std::to_string(acc);
}

std::string Day07::part2(const std::vector<std::string> &lines) {
    size_t acc{};
    size_t target{};
    std::vector<size_t> nums{};
    for (const auto &line : lines) {
        parse(line, target, nums);
        acc += calibrationResultConcat(target, nums.at(0), nums, 0) ? target : 0;
    }
    return std::to_string(acc);
}

void Day07::parse(const std::string &line, size_t &target, std::vector<size_t> &numbers) {
    numbers.clear();
    const size_t colon_pos = line.find(':');
    target = std::stoul(line.substr(0, colon_pos));
    std::stringstream str(line.substr(colon_pos + 2));
    std::string num{};
    while (std::getline(str, num, ' ')) {
        numbers.push_back(std::stoi(num));
    }
}

bool Day07::calibrationResult(size_t target, size_t result, const std::vector<size_t> &numbers,
    size_t idx) {

    if (numbers.size() == ++idx) {
        return target == result;
    }
    if (result > target) {
        return false;
    }
    return calibrationResult(target, result + numbers.at(idx), numbers, idx) ||
           calibrationResult(target, result * numbers.at(idx), numbers, idx);
}

bool Day07::calibrationResultConcat(size_t target, size_t result,
    const std::vector<size_t> &numbers, size_t idx) {

    if (numbers.size() == ++idx) {
        return target == result;
    }
    if (result > target) {
        return false;
    }
    size_t res = result;
    size_t right = numbers.at(idx);
    while (right) {
        res *= 10;
        right /= 10;
    }

    return calibrationResultConcat(target, result + numbers.at(idx), numbers, idx) ||
           calibrationResultConcat(target, result * numbers.at(idx), numbers, idx) ||
           calibrationResultConcat(target, res + numbers.at(idx), numbers, idx);
}
} // namespace aoc
