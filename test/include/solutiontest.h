
#ifndef __AOC_SOLUTIONTEST_H__
#define __AOC_SOLUTIONTEST_H__

#include "solution/Solution.h"
#include "util/fileread.h"

#include <cstddef>
#include <gtest/gtest.h>
#include <iomanip>
#include <sstream>
#include <string>

class DayTestYear : public ::testing::Test {

private:
    const std::string base_path = "../../resources/day";

protected:
    /**
     * Simple test function to verify solutions for each day so far with unit tests.
     * @param day the day to test
     * @param part1 expected solution for part 1
     * @param part2 expected solution for part 2
     */
    void testSolution(const size_t day, const std::string &part1, const std::string &part2) {

        std::ostringstream input_file{};
        input_file << base_path << std::setw(2) << std::setfill('0') << day << ".txt";

        const auto solution = aoc::Solution::getDay(day);

        const std::vector<std::string> lines = aoc::readInput(input_file.str());

        const std::string p1_actual = solution->part1(lines);
        const std::string p2_actual = solution->part2(lines);

        ASSERT_EQ(part1, p1_actual)
            << "Expected " << part1 << " for day " << day << " part 1 but got " << p1_actual;
        ASSERT_EQ(part2, p2_actual)
            << "Expected " << part2 << " for day " << day << " part 2 but got " << p2_actual;
    }
};

#endif
