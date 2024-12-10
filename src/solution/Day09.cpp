
#include "solution/Day09.h"
#include <utility>

namespace aoc {

std::string Day09::part1(const std::vector<std::string> &lines) {
    auto files = parseFilesystem(lines.at(0));
    compressBlocks(files);
    return std::to_string(computeChecksum(files));
}

std::string Day09::part2(const std::vector<std::string> &lines) {
    auto files = parseFilesystem(lines.at(0));
    compressFiles(files);
    return std::to_string(computeChecksum(files));
}

std::vector<int32_t> Day09::parseFilesystem(const std::string &line) {

    std::vector<int32_t> ret{};
    int32_t id{};

    for (auto iter = line.begin(); iter != line.end(); ++iter) {
        for (size_t used_count = 0; used_count < static_cast<size_t>(*iter - '0');
             ++used_count) {
            ret.push_back(id);
        }
        ++id;
        if (++iter == line.end()) {
            break;
        }
        for (size_t free_count = 0; free_count < static_cast<size_t>(*iter - '0');
             ++free_count) {
            ret.push_back(-1);
        }
    }
    return ret;
}

void Day09::compressBlocks(std::vector<int32_t> &files) {

    size_t idx_left{};
    size_t idx_right{files.size()};

    while (idx_left < idx_right) {
        if (-1 == files.at(idx_left)) {
            while (-1 == files.at(--idx_right)) {
                if (idx_left >= idx_right) {
                    return;
                }
            }
            std::swap(files.at(idx_left), files.at(idx_right));
        }
        ++idx_left;
    }
}

void Day09::compressFiles(std::vector<int32_t> &files) {

    size_t idx{files.size()};
    while (0 < --idx) {
        if (-1 != files.at(idx)) {
            const int32_t id = files.at(idx);
            const size_t right = idx;
            while (id == files.at(idx)) {
                if (0 == --idx) {
                    return;
                }
            }
            const size_t size = right - idx;
            ++idx;
            int64_t free_idx = getFreeIdx(files, size);
            if (-1 == free_idx || static_cast<size_t>(free_idx) > idx) {
                continue;
            }
            for (size_t offset = 0; offset < size; ++offset) {
                std::swap(files.at(idx + offset), files.at(free_idx + offset));
            }
        }
    }
}

size_t Day09::computeChecksum(const std::vector<int32_t> &files) {

    size_t checksum{};
    for (size_t idx = 0; idx < files.size(); ++idx) {
        checksum += idx * (-1 == files.at(idx) ? 0 : files.at(idx));
    }
    return checksum;
}

int64_t Day09::getFreeIdx(const std::vector<int32_t> &files, const int64_t size) {

    const int64_t files_size = static_cast<int64_t>(files.size());
    for (int64_t idx = 0; idx < files_size; ++idx) {
        if (-1 == files.at(idx)) {
            const int64_t left = idx;
            while (files_size > idx && -1 == files.at(idx)) {
                ++idx;
            }
            if (idx - left >= size) {
                return left;
            }
        }
    }
    return -1;
}
} // namespace aoc
