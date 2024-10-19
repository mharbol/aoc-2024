
#include "solution/Day00.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace aoc {

std::string Day00::part1(const std::vector<std::string> &lines) {
    size_t tot_vert{}, tot_horz{};
    for (const auto &block : getBlocks(lines)) {
        tot_vert += getReflectionIdx(getVertBitRepr(block));
        tot_horz += getReflectionIdx(getHorzBitRepr(block));
    }
    return std::to_string(tot_horz * 100 + tot_vert);
}

std::string Day00::part2(const std::vector<std::string> &lines) {
    size_t tot_vert{}, tot_horz{};
    for (const auto &block : getBlocks(lines)) {
        tot_vert += getSmudgeReflectionIdx(getVertBitRepr(block));
        tot_horz += getSmudgeReflectionIdx(getHorzBitRepr(block));
    }
    return std::to_string(tot_horz * 100 + tot_vert);
}

size_t Day00::getReflectionIdx(const std::vector<uint32_t> &vec) {
    for (size_t idx = 0; idx < vec.size() - 1; idx++) {
        if (isReflectionIdx(idx, vec)) {
            return idx + 1;
        }
    }
    return 0;
}

size_t Day00::getSmudgeReflectionIdx(const std::vector<uint32_t> &vec) {
    for (size_t idx = 0; idx < vec.size() - 1; ++idx) {
        if (isSmudgeReflectionIdx(idx, vec)) {
            return idx + 1;
        }
    }
    return 0;
}

bool Day00::isReflectionIdx(const size_t idx, const std::vector<uint32_t> &vec) {

    int32_t left = idx;
    size_t right = idx + 1;

    while (left >= 0 && right < vec.size()) {
        if (vec.at(left) != vec.at(right)) {
            return false;
        }
        --left;
        ++right;
    }
    return true;
}

bool Day00::isSmudgeReflectionIdx(const size_t idx, const std::vector<uint32_t> &vec) {
    int32_t left = idx;
    size_t right = idx + 1;
    size_t pow_2_count{};

    while (left >= 0 && right < vec.size()) {
        const bool is_pow_2 = isPow2(vec.at(right) ^ vec.at(left));
        if (vec.at(left) != vec.at(right) && !is_pow_2) {
            return false;
        }
        pow_2_count += is_pow_2 ? 1 : 0;
        --left;
        ++right;
    }
    return 1 == pow_2_count;
}

std::vector<std::vector<std::string>> Day00::getBlocks(const std::vector<std::string> &lines) {
    std::vector<std::vector<std::string>> ret;
    std::vector<std::string> curr_vec;
    for (auto &line : lines) {
        if (line.empty()) {
            ret.push_back(std::move(curr_vec));
            curr_vec.clear();
        } else {
            curr_vec.push_back(line);
        }
    }
    ret.push_back(std::move(curr_vec));
    return ret;
}

std::vector<uint32_t> Day00::getHorzBitRepr(const std::vector<std::string> &block) {
    std::vector<uint32_t> ret;
    for (const auto &line : block) {
        uint32_t num{};
        for (const auto &character : line) {
            if ('#' == character) {
                num |= 1;
            }
            num <<= 1;
        }
        ret.push_back(num);
    }
    return ret;
}

std::vector<uint32_t> Day00::getVertBitRepr(const std::vector<std::string> &block) {
    std::vector<uint32_t> ret;
    for (size_t col = 0; col < block.at(0).length(); ++col) {
        uint32_t num{};
        for (size_t row = 0; row < block.size(); ++row) {
            if ('#' == block.at(row).at(col)) {
                num |= 1;
            }
            num <<= 1;
        }
        ret.push_back(num);
    }
    return ret;
}

bool Day00::isPow2(const uint32_t num) {
    return (num != 0) && ((num & (num - 1)) == 0);
}
} // namespace aoc
