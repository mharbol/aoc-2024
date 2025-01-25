
#include "solution/Day25.h"
#include <string>
#include <vector>

namespace aoc {

std::string Day25::part1(const std::vector<std::string> &lines) {
    const auto &[locks, keys] = parse(lines);

    size_t count{};
    for (const auto &lock : locks) {
        for (const auto &key : keys) {
            count += fits(lock, key);
        }
    }

    return std::to_string(count);
}

std::string Day25::part2(const std::vector<std::string> &) {
    return "";
}

std::pair<std::vector<lockkey_t>, std::vector<lockkey_t>> Day25::parse(
    const std::vector<std::string> &lines) {

    std::vector<lockkey_t> locks{}, keys{};

    auto iter = lines.begin();
    for (;;) {
        bool is_lock = "#####" == *iter++;
        lockkey_t lock_key{};
        while (!iter->empty() && iter != lines.end()) {
            std::get<0>(lock_key) += iter->at(0) == '#';
            std::get<1>(lock_key) += iter->at(1) == '#';
            std::get<2>(lock_key) += iter->at(2) == '#';
            std::get<3>(lock_key) += iter->at(3) == '#';
            std::get<4>(lock_key) += iter->at(4) == '#';
            ++iter;
        }
        if (is_lock) {
            locks.push_back(lock_key);
        } else {
            keys.push_back(lock_key);
        }
        if (iter == lines.end()) {
            break;
        }
        ++iter;
    }

    return {locks, keys};
}

bool Day25::fits(const lockkey_t &lock, const lockkey_t &key) const {
    return (std::get<0>(lock) + std::get<0>(key) < 7) &&
           (std::get<1>(lock) + std::get<1>(key) < 7) &&
           (std::get<2>(lock) + std::get<2>(key) < 7) &&
           (std::get<3>(lock) + std::get<3>(key) < 7) &&
           (std::get<4>(lock) + std::get<4>(key) < 7);
}
} // namespace aoc
