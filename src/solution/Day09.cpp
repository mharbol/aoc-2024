
#include "solution/Day09.h"
#include <cstddef>
#include <string>

namespace aoc {

std::string Day09::part1(const std::vector<std::string> &lines) {
    const auto &files = parseFilesystem(lines.at(0));
    return std::to_string(getChecksum(files));
}

std::string Day09::part2(const std::vector<std::string> &) {
    return "";
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
        if (++iter != line.end()) {
            for (size_t free_count = 0; free_count < static_cast<size_t>(*iter - '0');
                 ++free_count) {
                ret.push_back(-1);
            }
        } else {
            --iter;
        }
    }
    return ret;
}

size_t Day09::getChecksum(const std::vector<int32_t> &files) {

    size_t checksum{};
    size_t idx_left{};
    size_t idx_right{files.size()};

    while (idx_left < idx_right) {
        if (-1 != files.at(idx_left)) {
            checksum += files.at(idx_left) * idx_left;
        } else {
            while (-1 == files.at(--idx_right)) {
                // ...
            }
            if (idx_left < idx_right) {
                checksum += files.at(idx_right) * idx_left;
            }
        }
        ++idx_left;
    }

    return checksum;
}
} // namespace aoc
