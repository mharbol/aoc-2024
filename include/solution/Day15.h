
#ifndef __AOC_DAY_15_H__
#define __AOC_DAY_15_H__

#include "Solution.h"
#include <string>
#include <utility>
#include <vector>

namespace aoc {
class LanternfishWarehouse {
private:
    std::vector<std::string> warehouse;
    size_t robo_row, robo_col;
    size_t width, height;

public:
    LanternfishWarehouse(std::vector<std::string> &&warehouse);
    ~LanternfishWarehouse() = default;
    void pushBox(const char dir);
    size_t sumGPS();
};

class Day15 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::pair<LanternfishWarehouse, std::vector<std::string>> parse(
        const std::vector<std::string> &lines);
};
} // namespace aoc
#endif
