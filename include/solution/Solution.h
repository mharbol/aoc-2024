
#ifndef __AOC_SOLUTION_H__
#define __AOC_SOLUTION_H__

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
namespace aoc {
/**
 * Base class for all day solutions. Each day extends Solution and overrides
 * `part1()` and `part2()`.
 */
class Solution {
public:
    /**
     * Getter for the Solution class for the given day.
     * @param day day number for the desired Solution
     * @return the associated Solution object if it exists, otherwise `nullptr`
     */
    static std::unique_ptr<Solution> getDay(size_t day);

    /**
     * The solution for part 1.
     * @param lines the contents of the problem input
     * @return the solution to part 1
     */
    virtual std::string part1(const std::vector<std::string> &lines) = 0;

    /**
     * The solution for part 2.
     * @param lines the contents of the problem input
     * @return the solution to part 2
     */
    virtual std::string part2(const std::vector<std::string> &lines) = 0;

    virtual ~Solution() = default;
};
} // namespace aoc

#endif
