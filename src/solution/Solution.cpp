#include "solution/Solution.h"
#include "solution/Day00.h"
#include "solution/Day01.h"
#include "solution/Day02.h"
#include "solution/Day03.h"
#include "solution/Day04.h"
#include "solution/Day05.h"
#include "solution/Day06.h"
#include "solution/Day07.h"
#include "solution/Day08.h"
#include "solution/Day09.h"
#include "solution/Day10.h"
#include "solution/Day11.h"
#include "solution/Day12.h"
#include "solution/Day13.h"
#include "solution/Day14.h"
#include "solution/Day15.h"
#include "solution/Day16.h"
#include "solution/Day17.h"
#include "solution/Day18.h"
#include "solution/Day19.h"
#include "solution/Day20.h"
#include "solution/Day21.h"
#include "solution/Day22.h"
#include "solution/Day23.h"
#include "solution/Day24.h"
#include "solution/Day25.h"
#include <cstddef>
#include <memory>

std::unique_ptr<aoc::Solution> aoc::Solution::getDay(size_t day) {
    switch (day) {
        case 0: return std::make_unique<aoc::Day00>();
        case 1: return std::make_unique<aoc::Day01>();
        case 2: return std::make_unique<aoc::Day02>();
        case 3: return std::make_unique<aoc::Day03>();
        case 4: return std::make_unique<aoc::Day04>();
        case 5: return std::make_unique<aoc::Day05>();
        case 6: return std::make_unique<aoc::Day06>();
        case 7: return std::make_unique<aoc::Day07>();
        case 8: return std::make_unique<aoc::Day08>();
        case 9: return std::make_unique<aoc::Day09>();
        case 10: return std::make_unique<aoc::Day10>();
        case 11: return std::make_unique<aoc::Day11>();
        case 12: return std::make_unique<aoc::Day12>();
        case 13: return std::make_unique<aoc::Day13>();
        case 14: return std::make_unique<aoc::Day14>();
        case 15: return std::make_unique<aoc::Day15>();
        case 16: return std::make_unique<aoc::Day16>();
        case 17: return std::make_unique<aoc::Day17>();
        case 18: return std::make_unique<aoc::Day18>();
        case 19: return std::make_unique<aoc::Day19>();
        case 20: return std::make_unique<aoc::Day20>();
        case 21: return std::make_unique<aoc::Day21>();
        case 22: return std::make_unique<aoc::Day22>();
        case 23: return std::make_unique<aoc::Day23>();
        case 24: return std::make_unique<aoc::Day24>();
        case 25: return std::make_unique<aoc::Day25>();
        default: return nullptr;
    }
}
