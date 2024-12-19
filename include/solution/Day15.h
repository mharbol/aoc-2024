
#ifndef __AOC_DAY_15_H__
#define __AOC_DAY_15_H__

#include "Solution.h"

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
    void pushWideBox(const char dir);
    bool canPushWideVert(const size_t row, const size_t col, const int32_t dr);
    bool canPushWideHorz(const size_t row, const size_t col, const int32_t dc);
    void pushWideVert(const size_t row, const size_t col, const int32_t dr);
    void pushWideHorz(const size_t row, const size_t col, const int32_t dc);
    size_t sumGPS();
    size_t sumWideGPS();
};

class Day15 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    std::pair<LanternfishWarehouse, std::vector<std::string>> parse(
        const std::vector<std::string> &lines);
    std::pair<LanternfishWarehouse, std::vector<std::string>> parseWide(
        const std::vector<std::string> &lines);
};
} // namespace aoc
#endif
