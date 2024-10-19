
#include "solution/Solution.h"
#include "solution/Day00.h"
#include <cstddef>
#include <memory>

std::unique_ptr<aoc::Solution> aoc::Solution::getDay(size_t day) {
    switch (day) {
        case 0: return std::make_unique<aoc::Day00>();
        default: return nullptr;
    }
}
