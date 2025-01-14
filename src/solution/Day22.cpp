
#include "solution/Day22.h"
#include <unordered_set>

namespace aoc {

std::string Day22::part1(const std::vector<std::string> &lines) {
    size_t acc{};
    for (const auto &line : lines) {
        size_t secret = std::stoul(line);
        for (size_t i = 0; i < 2000; ++i) {
            secret = calcNewSecret(secret);
        }
        acc += secret;
    }
    return std::to_string(acc);
}

std::string Day22::part2(const std::vector<std::string> &lines) {
    std::unordered_map<uint64_t, size_t> map{};
    size_t most{};
    for (const auto &line : lines) {
        mostBananas(std::stoul(line), map, most);
    }
    return std::to_string(most);
}

size_t Day22::calcNewSecret(size_t seed) {
    seed = ((seed * 64) ^ seed) % 16777216;
    seed = ((seed / 32) ^ seed) % 16777216;
    return ((seed * 2048) ^ seed) % 16777216;
}

void Day22::mostBananas(size_t secret, std::unordered_map<uint64_t, size_t> &seq_payoff,
    size_t &curr_max) {

    uint64_t seq_key{};
    std::unordered_set<uint64_t> visited{};
    int32_t price{};

    shiftSecret(secret, price, seq_key);
    shiftSecret(secret, price, seq_key);
    shiftSecret(secret, price, seq_key);
    for (size_t i = 3; i < 2000; ++i) {
        shiftSecret(secret, price, seq_key);
        if (!visited.contains(seq_key)) {
            visited.insert(seq_key);
            if (size_t val = seq_payoff[seq_key] += price; val > curr_max) {
                curr_max = val;
            }
        }
    }
}

void Day22::shiftSecret(size_t &secret, int32_t &prev_price, uint64_t &tup) {

    int32_t curr_price = secret % 10;
    secret = calcNewSecret(secret);
    tup = ((tup << 5) & 0xfffff) + curr_price - prev_price + 9;

    prev_price = curr_price;
}
} // namespace aoc
