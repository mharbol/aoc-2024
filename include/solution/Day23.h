
#ifndef __AOC_DAY_23_H__
#define __AOC_DAY_23_H__

#include "Solution.h"
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace aoc {
class Day23 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    void bronKerboschPivot(std::set<std::string> &R, std::unordered_set<std::string> &P,
        std::unordered_set<std::string> &X,
        const std::unordered_map<std::string, std::unordered_set<std::string>> &graph,
        std::set<std::string> &ret);
};
} // namespace aoc
#endif
