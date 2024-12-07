
#include "solution/Day07.h"
#include <sstream>

namespace aoc {

std::string Day07::part1(const std::vector<std::string> &lines) {
    size_t acc{};
    size_t target{};
    std::vector<size_t> nums{};
    for (const auto &line : lines) {
        parse(line, target, nums);
        acc += calibrationResult(target, nums.at(0), nums, 0);
    }
    return std::to_string(acc);
}

std::string Day07::part2(const std::vector<std::string> &lines) {
    size_t acc{};
    size_t target{};
    std::vector<size_t> nums{};
    for (const auto &line : lines) {
        parse(line, target, nums);
        acc += calibrationResultConcat(target, nums.at(0), nums, 0);
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

size_t Day07::calibrationResult(size_t target, size_t result,
    const std::vector<size_t> &numbers, size_t idx) {

    if (numbers.size() == ++idx) {
        return (target == result) ? target : 0;
    }
    return (target == calibrationResult(target, result + numbers.at(idx), numbers, idx) ||
               target == calibrationResult(target, result * numbers.at(idx), numbers, idx)) ? target : 0;
}

size_t Day07::calibrationResultConcat(size_t tgt, size_t result,
    const std::vector<size_t> &numbers, size_t idx) {

    if (numbers.size() == ++idx) {
        return (tgt == result) ? tgt : 0;
    }
    std::stringstream ss{};
    ss << result << numbers.at(idx);
    const size_t concat_res = std::stoul(ss.str());
    return (tgt == calibrationResultConcat(tgt, result + numbers.at(idx), numbers, idx) ||
               tgt == calibrationResultConcat(tgt, result * numbers.at(idx), numbers, idx)) ||
                   tgt == calibrationResultConcat(tgt, concat_res, numbers, idx) ? tgt : 0;
}
} // namespace aoc
