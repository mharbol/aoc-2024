
#ifndef __AOC_DAY_09_H__
#define __AOC_DAY_09_H__

#include "Solution.h"
#include <cstdint>
#include <string>
#include <vector>

namespace aoc {

class Day09 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::vector<int32_t> parseFilesystem(const std::string &line);
    void compressBlocks(std::vector<int32_t> &files);
    void compressFiles(std::vector<int32_t> &files);
    size_t computeChecksum(const std::vector<int32_t> &files);
    int64_t getFreeIdx(const std::vector<int32_t> &files, const int64_t size);
};
} // namespace aoc
#endif
