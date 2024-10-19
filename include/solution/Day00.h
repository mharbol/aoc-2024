
#ifndef __AOC_DAY_00_H__
#define __AOC_DAY_00_H__

#include "Solution.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
namespace aoc {
class Day00 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    size_t getReflectionIdx(const std::vector<uint32_t> &vec);
    size_t getSmudgeReflectionIdx(const std::vector<uint32_t> &vec);
    bool isReflectionIdx(const size_t idx, const std::vector<uint32_t> &vec);
    bool isSmudgeReflectionIdx(const size_t idx, const std::vector<uint32_t> &vec);
    bool isPow2(const uint32_t num);
    std::vector<std::vector<std::string>> getBlocks(const std::vector<std::string> &lines);
    std::vector<uint32_t> getHorzBitRepr(const std::vector<std::string> &block);
    std::vector<uint32_t> getVertBitRepr(const std::vector<std::string> &block);
};
} // namespace aoc
#endif
