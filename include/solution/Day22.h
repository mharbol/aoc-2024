
#ifndef __AOC_DAY_22_H__
#define __AOC_DAY_22_H__

#include "Solution.h"
#include <unordered_map>

namespace aoc {
class Day22 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    size_t calcNewSecret(const size_t seed);
    void mostBananas(const size_t seed, std::unordered_map<uint64_t, size_t> &seq_payoff,
        size_t &curr_max);
    void shiftSecret(size_t &secret, int32_t &prev_price, uint64_t &tup);
};
} // namespace aoc
#endif
