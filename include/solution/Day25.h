
#ifndef __AOC_DAY_25_H__
#define __AOC_DAY_25_H__

#include "Solution.h"
#include <cstddef>
#include <utility>
#include <vector>

namespace aoc {
class Day25 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    struct LockKey {
        LockKey() = default;
        ~LockKey() = default;
        size_t s0{}, s1{}, s2{}, s3{}, s4{};
        bool fits(const LockKey &other) const;
    };
    std::pair<std::vector<LockKey>, std::vector<LockKey>> parse(
        const std::vector<std::string> &lines);
};
} // namespace aoc
#endif
