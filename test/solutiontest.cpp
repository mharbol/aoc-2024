
#include "solution/Solution.h"
#include "solutiontest.h"
#include "tools/fileread.h"
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

namespace aoc {

void testSolution(size_t day, const std::string part1, const std::string part2) {

    std::ostringstream input_file{};

    input_file << "../../resources/" << "day" << std::setw(2) << std::setfill('0') << day
               << ".txt";

    const auto solution = Solution::getDay(day);

    const std::vector<std::string> lines = aoc::readInput(input_file.str());

    const std::string p1_actual = solution->part1(lines);
    const std::string p2_actual = solution->part2(lines);

    ASSERT_EQ(part1, p1_actual) << "Expected " << part1 << " for day " << day
                                << " part 1 but got " << p1_actual;
    ASSERT_EQ(part2, p2_actual) << "Expected " << part2 << " for day " << day
                                << " part 2 but got " << p2_actual;
}
} // namespace aoc
