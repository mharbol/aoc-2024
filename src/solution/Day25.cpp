
#include "solution/Day25.h"
#include <string>
#include <vector>

namespace aoc {

std::string Day25::part1(const std::vector<std::string> &lines) {
    const auto &[locks, keys] = parse(lines);

    size_t count{};
    for (const auto &lock : locks) {
        for (const auto &key : keys) {
            count += lock.fits(key);
        }
    }

    return std::to_string(count);
}

std::string Day25::part2(const std::vector<std::string> &) {
    return "";
}

std::pair<std::vector<Day25::LockKey>, std::vector<Day25::LockKey>> Day25::parse(
    const std::vector<std::string> &lines) {

    std::vector<LockKey> locks{}, keys{};

    for (auto iter = lines.begin(); iter != lines.end();) {
        bool is_lock = "#####" == *iter++;
        LockKey lock_key{};
        while (!iter->empty() && iter != lines.end()) {
            lock_key.s0 += iter->at(0) == '#';
            lock_key.s1 += iter->at(1) == '#';
            lock_key.s2 += iter->at(2) == '#';
            lock_key.s3 += iter->at(3) == '#';
            lock_key.s4 += iter->at(4) == '#';
            ++iter;
        }
        if (is_lock) {
            locks.push_back(lock_key);
        } else {
            keys.push_back(lock_key);
        }
        if (iter != lines.end()) {
            ++iter;
        }
    }

    return {locks, keys};
}

bool Day25::LockKey::fits(const LockKey &other) const {
    return (s0 + other.s0 < 7) && (s1 + other.s1 < 7) && (s2 + other.s2 < 7) &&
           (s3 + other.s3 < 7) && (s4 + other.s4 < 7);
}
} // namespace aoc
