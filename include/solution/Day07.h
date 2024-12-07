
#ifndef __AOC_DAY_07_H__
#define __AOC_DAY_07_H__

#include "Solution.h"
#include <vector>

namespace aoc {
class Day07 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    void parse(const std::string &line, size_t &target, std::vector<size_t> &numbers);
    size_t calibrationResult(size_t target, size_t result, const std::vector<size_t> &numbers,
        size_t idx);
    size_t calibrationResultConcat(size_t target, size_t result,
        const std::vector<size_t> &numbers, size_t idx);
};
} // namespace aoc
#endif
