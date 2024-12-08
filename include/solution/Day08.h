
#ifndef __AOC_DAY_08_H__
#define __AOC_DAY_08_H__

#include "Solution.h"
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace aoc {
class Day08 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::map<char, std::vector<std::pair<int32_t, int32_t>>> getAntennas(
        const std::vector<std::string> &lines);
};
} // namespace aoc
#endif
