
#ifndef __AOC_DAY_21_H__
#define __AOC_DAY_21_H__

#include "Solution.h"
#include <map>
#include <utility>

namespace aoc {
class Day21 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::map<std::pair<std::string, size_t>, size_t> ideal_trav_cache{};

    std::vector<std::string> numpadPaths(const char start, const char end);
    std::vector<std::string> arrowpadPaths(const char start, const char end);

    std::pair<int32_t, int32_t> numpadRowCol(const char loc);
    std::pair<int32_t, int32_t> arrowRowCol(const char loc);
    std::vector<std::string> keypadPaths(const std::pair<int32_t, int32_t> &,
        const std::pair<int32_t, int32_t> &, const std::pair<int32_t, int32_t> &,
        const std::string &);

    std::vector<std::string> allNumpadTravs(const std::string &seq);
    std::vector<std::string> allArrowpadTravs(const std::string &seq);
    std::vector<std::string> allSubseqs(const std::string &seq);

    size_t idealTravLength(const std::string &seq, const size_t depth);
    size_t idealTravLengthSubs(const std::string &subseq, const size_t depth);
};
} // namespace aoc
#endif
