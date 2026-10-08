
#ifndef _AOC_DAY_25_H_
#define _AOC_DAY_25_H_

#include "Solution.h"
#include <utility>
#include <vector>

namespace aoc {
class Day25 : public Solution {

private:
    typedef std::tuple<uint_fast8_t, uint_fast8_t, uint_fast8_t, uint_fast8_t, uint_fast8_t>
        lockkey_t;

public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::pair<std::vector<lockkey_t>, std::vector<lockkey_t>> parse(
        const std::vector<std::string> &lines);
    bool fits(const lockkey_t &lock, const lockkey_t &key) const;
};
} // namespace aoc
#endif
