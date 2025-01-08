
#ifndef __AOC_DAY_23_H__
#define __AOC_DAY_23_H__

#include "Solution.h"
#include <map>
#include <set>

namespace aoc {
class Day23 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    void bronKerbosch(std::set<std::string> &R, std::set<std::string> &P,
        std::set<std::string> &X, const std::map<std::string, std::set<std::string>> &graph,
        std::set<std::string> &ret);
};
} // namespace aoc
#endif
