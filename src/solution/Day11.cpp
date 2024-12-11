
#include "solution/Day11.h"
#include <sstream>
#include <utility>

namespace aoc {

std::string Day11::part1(const std::vector<std::string> &lines) {
    auto stones = parse(lines.at(0));
    size_t acc{};
    cache.clear();
    for (const auto stone : stones) {
        acc += expandStone(stone, 25);
    }
    return std::to_string(acc);
}

std::string Day11::part2(const std::vector<std::string> &lines) {
    auto stones = parse(lines.at(0));
    size_t acc{};
    cache.clear();
    for (const auto stone : stones) {
        acc += expandStone(stone, 75);
    }
    return std::to_string(acc);
}

std::vector<uint64_t> Day11::parse(const std::string &line) {
    std::vector<uint64_t> stones{};
    std::stringstream str(line);
    std::string stone{};
    while (std::getline(str, stone, ' ')) {
        stones.push_back(std::stoul(stone));
    }
    return stones;
}

size_t Day11::digitSplit(uint64_t stone) {
    size_t count = 0;
    size_t div = 1;
    while (stone) {
        stone /= 10;
        if (0 == ++count % 2) {
            div *= 10;
        }
    }
    if (0 == count % 2) {
        return div;
    }
    return 0;
}

size_t Day11::expandStone(uint64_t stone, size_t remaining) {
    if (0 == remaining) {
        return 1;
    }
    const std::pair<uint64_t, size_t> key(stone, remaining);
    size_t val{};
    if (cache.contains(key)) {
        return cache.at(key);
    }
    if (0 == stone) {
        val = expandStone(1, remaining - 1);
    } else if (size_t ds = digitSplit(stone)) {
        val = expandStone(stone / ds, remaining - 1) + expandStone(stone % ds, remaining - 1);
    } else {
        val = expandStone(stone * 2024, remaining - 1);
    }
    cache[key] = val;
    return val;
}

// Original Part 1 Solution (repeat 25 times)
void Day11::blink(std::vector<uint64_t> &stones) {
    std::vector<uint64_t> new_stones{};
    for (auto stone : stones) {
        if (0 == stone) {
            new_stones.push_back(1);
        } else if (size_t div = digitSplit(stone)) {
            new_stones.push_back(stone / div);
            new_stones.push_back(stone % div);
        } else {
            new_stones.push_back(stone * 2024);
        }
    }
    stones = std::move(new_stones);
}
} // namespace aoc
