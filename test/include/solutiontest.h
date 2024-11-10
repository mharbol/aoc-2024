
#ifndef __AOC_SOLUTIONTEST_H__
#define __AOC_SOLUTIONTEST_H__

#include <cstddef>
#include <string>
namespace aoc {
/**
 * Simple test function to verify solutions for each day so far with unit tests.
 * @param day the day to test
 * @param part1 expected solution for part 1
 * @param part2 expected solution for part 2
 */
void testSolution(const size_t day, const std::string &part1, const std::string &part2);
} // namespace aoc

#endif
