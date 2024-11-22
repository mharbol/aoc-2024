#include "solution/Solution.h"
#include "tools/ArgParse.h"
#include "tools/fileread.h"
#include <iostream>

int main(const int argc, const char **const argv) {

    aoc::ArgParse args{};

    const aoc::ArgParse::Status status = args.parseArgs(argc, argv);

    if (aoc::ArgParse::Status::HELP == status) {
        args.showHelp();
        return 0;
    } else if (aoc::ArgParse::Status::FAIL == status) {
        std::cout << args.getErrorMsg() << "\n\n";
        args.showUsage();
        return 1;
    }

    const auto lines = aoc::readInput(args.getFilePath());
    const auto solution = aoc::Solution::getDay(args.getDay());
    if (nullptr == solution) {
        std::cout << "No Solution for day " << args.getDay() << "." << std::endl;
        return 1;
    }
    if (1 == args.getPart()) {
        std::cout << solution->part1(lines) << std::endl;
    } else {
        std::cout << solution->part2(lines) << std::endl;
    }
    return 0;
}
