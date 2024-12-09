
#ifndef __AOC_DAY_09_H__
#define __AOC_DAY_09_H__

#include "Solution.h"
#include <string>
#include <vector>

namespace aoc {

class Day09 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::vector<int32_t> parseFilesystem(const std::string &line);
    size_t getChecksum(const std::vector<int32_t> &files);
};
} // namespace aoc
#endif
