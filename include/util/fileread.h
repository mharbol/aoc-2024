#ifndef _AOC_FILEREAD_H_
#define _AOC_FILEREAD_H_

#include <string>
#include <vector>
namespace aoc {
/**
 * Read the input from a given input file and return its contents. Assumes file exists.
 * @param file_path path to the desired input file
 * @return the contents of the file
 */
std::vector<std::string> readInput(const std::string &file_path) noexcept;
} // namespace aoc

#endif
