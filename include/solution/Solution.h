
#ifndef __AOC_SOLUTION_H__
#define __AOC_SOLUTION_H__

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
namespace aoc {
class Solution {
public:
    static std::unique_ptr<Solution> getDay(size_t day);
    virtual std::string part1(const std::vector<std::string> &lines) = 0;
    virtual std::string part2(const std::vector<std::string> &lines) = 0;
    virtual ~Solution() = default;
};
} // namespace aoc

#endif
