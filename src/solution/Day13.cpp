
#include "solution/Day13.h"
#include <string>
#include <tuple>

namespace aoc {

std::string Day13::part1(const std::vector<std::string> &lines) {

    size_t acc{};

    for (const auto &[a, b, prize] : parse(lines)) {
        const int64_t det = a.x * b.y - b.x * a.y;
        const int64_t a_press = (prize.x * b.y - prize.y * b.x) / det;
        const int64_t b_press = (a.x * prize.y - a.y * prize.x) / det;
        if (prize.x == a_press * a.x + b_press * b.x &&
            prize.y == a_press * a.y + b_press * b.y) {
            acc += 3 * a_press + b_press;
        }
    }

    return std::to_string(acc);
}

std::string Day13::part2(const std::vector<std::string> &lines) {

    size_t acc{};

    for (auto [a, b, prize] : parse(lines)) {
        prize.x += 10000000000000;
        prize.y += 10000000000000;
        const int64_t det = a.x * b.y - b.x * a.y;
        const int64_t a_press = (prize.x * b.y - prize.y * b.x) / det;
        const int64_t b_press = (a.x * prize.y - a.y * prize.x) / det;
        if (prize.x == a_press * a.x + b_press * b.x &&
            prize.y == a_press * a.y + b_press * b.y) {
            acc += 3 * a_press + b_press;
        }
    }

    return std::to_string(acc);
}

std::vector<std::tuple<Button, Button, Button>> Day13::parse(
    const std::vector<std::string> &lines) {

    std::vector<std::tuple<Button, Button, Button>> ret{};

    for (auto iter = lines.begin(); iter != lines.end(); ++iter) {
        if (iter->empty()) {
            ++iter;
        }
        Button a{};
        size_t comma_pos = iter->find(',');
        a.x = std::stoul(iter->substr(12, comma_pos - 12));
        a.y = std::stoul(iter->substr(comma_pos + 4, iter->size() - comma_pos - 4));
        ++iter;

        Button b{};
        comma_pos = iter->find(',');
        b.x = std::stoul(iter->substr(12, comma_pos - 12));
        b.y = std::stoul(iter->substr(comma_pos + 4, iter->size() - comma_pos - 4));
        ++iter;

        Button prize{};
        comma_pos = iter->find(',');
        prize.x = std::stoul(iter->substr(9, comma_pos - 9));
        prize.y = std::stoul(iter->substr(comma_pos + 4, iter->size() - comma_pos - 4));
        ret.emplace_back(a, b, prize);
    }

    return ret;
}
} // namespace aoc
