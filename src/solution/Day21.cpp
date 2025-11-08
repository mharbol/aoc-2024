
#include "solution/Day21.h"
#include <algorithm>
#include <string>
#include <utility>
namespace aoc {

std::string Day21::part1(const std::vector<std::string> &lines) {
    return solve<2>(lines);
}

std::string Day21::part2(const std::vector<std::string> &lines) {
    return solve<25>(lines);
}

template <size_t DEPTH>
inline std::string Day21::solve(const std::vector<std::string> &lines) {
    ideal_trav_cache.clear();
    size_t acc{};
    for (const auto &code : lines) {
        size_t min_len = ~0;
        for (const auto &trav : allNumpadTravs(code)) {
            min_len = std::min(min_len, idealTravLength(trav, DEPTH));
        }
        acc += min_len * std::stoul(code.substr(0, 3));
    }
    return std::to_string(acc);
}

size_t Day21::idealTravLength(const std::string &seq, const size_t depth) {

    if (0 == depth) {
        return seq.size();
    }
    if (ideal_trav_cache.contains({seq, depth})) {
        return ideal_trav_cache.at({seq, depth});
    }
    size_t len = 0;
    for (const auto &subseq : allSubseqs(seq)) {
        len += idealTravLengthSubs(subseq, depth);
    }
    ideal_trav_cache[{seq, depth}] = len;
    return len;
}

size_t Day21::idealTravLengthSubs(const std::string &subseq, const size_t depth) {

    if (ideal_trav_cache.contains({subseq, depth})) {
        return ideal_trav_cache.at({subseq, depth});
    }
    size_t min_len = ~0;
    for (const auto &trav : allArrowpadTravs(subseq)) {
        if (size_t len = idealTravLength(trav, depth - 1); len < min_len) {
            min_len = len;
        }
    }
    ideal_trav_cache[{subseq, depth}] = min_len;
    return min_len;
}

std::vector<std::string> Day21::allSubseqs(const std::string &seq) {

    size_t pos;
    size_t prev{};
    std::vector<std::string> ret{};
    while ((pos = seq.find('A', prev)) != std::string::npos) {
        ret.push_back(seq.substr(prev, pos - prev + 1));
        prev = pos + 1;
    }
    return ret;
}

std::vector<std::string> Day21::allArrowpadTravs(const std::string &seq) {

    auto iter = seq.begin();
    char prev = 'A';
    std::vector<std::string> curr_vec{};
    std::vector<std::string> working_vec{""};
    do {
        curr_vec.clear();
        for (const auto &path : arrowpadPaths(prev, *iter)) {
            for (const auto &pre : working_vec) {
                curr_vec.push_back(pre + path);
            }
        }
        std::swap(working_vec, curr_vec);
        prev = *iter;
    } while (++iter != seq.end());
    return working_vec;
}

std::vector<std::string> Day21::allNumpadTravs(const std::string &seq) {

    auto iter = seq.begin();
    char prev = 'A';

    std::vector<std::string> curr_vec{};
    std::vector<std::string> ret_vec{""};
    do {
        curr_vec.clear();
        for (const auto &path : numpadPaths(prev, *iter)) {
            for (const auto &pre : ret_vec) {
                curr_vec.push_back(pre + path);
            }
        }
        std::swap(ret_vec, curr_vec);
        prev = *iter;
    } while (++iter != seq.end());
    return ret_vec;
}

std::vector<std::string> Day21::numpadPaths(const char start, const char end) {
    return keypadPaths(numpadRowCol(start), numpadRowCol(end), {3, 0}, "");
}

std::vector<std::string> Day21::arrowpadPaths(const char start, const char end) {
    return keypadPaths(arrowRowCol(start), arrowRowCol(end), {0, 0}, "");
}

std::vector<std::string> Day21::keypadPaths(const std::pair<int32_t, int32_t> &start,
    const std::pair<int32_t, int32_t> &end, const std::pair<int32_t, int32_t> &nogo,
    const std::string &seq) {

    if (start == end) {
        return {seq + 'A'};
    }
    if (start == nogo) {
        return {};
    }

    const int32_t vert = end.first - start.first;
    const int32_t horz = end.second - start.second;

    std::vector<std::string> ret{};

    if (0 != vert) {
        const int32_t vert_step = start.first + (vert < 0 ? -1 : 1);
        const std::string vert_seq(seq + (vert < 0 ? '^' : 'v'));
        for (auto &&s :
            keypadPaths(std::make_pair(vert_step, start.second), end, nogo, vert_seq)) {
            ret.push_back(std::move(s));
        }
    }
    if (0 != horz) {
        const int32_t horz_step = start.second + (horz < 0 ? -1 : 1);
        const std::string horz_seq(seq + (horz < 0 ? '<' : '>'));
        for (auto &&s :
            keypadPaths(std::make_pair(start.first, horz_step), end, nogo, horz_seq)) {
            ret.push_back(std::move(s));
        }
    }
    return ret;
}

std::pair<int32_t, int32_t> Day21::numpadRowCol(const char loc) {
    switch (loc) {
        case '0': return {3, 1};
        case 'A': return {3, 2};
        default: return {2 - (loc - '1') / 3, (loc - '1') % 3};
    }
}

std::pair<int32_t, int32_t> Day21::arrowRowCol(const char loc) {
    switch (loc) {
        case '^': return {0, 1};
        case 'v': return {1, 1};
        case '<': return {1, 0};
        case '>': return {1, 2};
        default: return {0, 2}; // case 'A'
    }
}
} // namespace aoc
