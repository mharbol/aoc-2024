
#include "solution/Day07.h"
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
    return calibrationResult(target, result + numbers.at(idx), numbers, idx) ||
           calibrationResult(target, result * numbers.at(idx), numbers, idx);
}

bool Day07::calibrationResultConcat(size_t target, size_t result,
    const std::vector<size_t> &numbers, size_t idx) {

    if (numbers.size() == ++idx) {
        return target == result;
    }
    std::stringstream ss{};
    ss << result << numbers.at(idx);
    const size_t concat_res = std::stoul(ss.str());
    return calibrationResultConcat(target, result + numbers.at(idx), numbers, idx) ||
           calibrationResultConcat(target, result * numbers.at(idx), numbers, idx) ||
           calibrationResultConcat(target, concat_res, numbers, idx);
}
} // namespace aoc
