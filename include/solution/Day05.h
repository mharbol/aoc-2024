
#ifndef __AOC_DAY_05_H__
#define __AOC_DAY_05_H__

#include "Solution.h"
#include <cstddef>
#include <map>
#include <set>
#include <vector>

namespace aoc {
class Day05 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::map<size_t, std::set<size_t>> getOrderRules(const std::vector<std::string> &);
    std::vector<std::vector<size_t>> getPages(const std::vector<std::string> &);
    bool verifyPages(const std::vector<size_t> &, const std::map<size_t, std::set<size_t>> &);
    size_t fixPages(const std::vector<size_t> &, const std::map<size_t, std::set<size_t>> &);
};
} // namespace aoc
#endif
