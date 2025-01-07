
#ifndef __AOC_DAY_22_H__
#define __AOC_DAY_22_H__

#include "Solution.h"
#include <map>
#include <tuple>

namespace aoc {
class Day22 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    size_t calcNewSecret(const size_t seed);
    void mostBananas(const size_t seed,
        std::map<std::tuple<int32_t, int32_t, int32_t, int32_t>, size_t> &seq_payoff,
        size_t &curr_max);
    void shiftTupleSecret(size_t &secret, int32_t &prev_price,
        std::tuple<int32_t, int32_t, int32_t, int32_t> &tup);
};
} // namespace aoc
#endif
