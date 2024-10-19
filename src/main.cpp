#include "solution/Solution.h"
#include "tools/ArgParse.h"
#include "tools/fileread.h"
#include <iostream>

int main(int argc, char **argv) {
    aoc::ArgParse args;
    if (!args.parseArgs(argc, argv)) {
        args.showErrors();
        return 1;
    }
    const auto lines = aoc::readInput(args.getFilePath());
    const auto solution = aoc::Solution::getDay(args.getDay());
    if (1 == args.getPart()) {
        std::cout << solution->part1(lines) << std::endl;
    } else {
        std::cout << solution->part2(lines) << std::endl;
    }
    return 0;
}
