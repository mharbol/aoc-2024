
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>

#include "tools/ArgParse.h"

namespace aoc {
bool ArgParse::parseArgs(int argc, char **argv) noexcept {
    day = 0;
    part = 0;
    input_file.clear();
    int opt;
    while ((opt = getopt(argc, argv, ":d:p:f:")) != -1) {
        switch (opt) {
            case 'd':
                if (!setInt(optarg, 0, 25, day)) {
                    errs.push_back("day");
                }
                break;
            case 'p':
                if (!setInt(optarg, 1, 2, part)) {
                    errs.push_back("part");
                }
                break;
            case 'f':
                input_file = std::string(optarg);
                if (!std::filesystem::exists(input_file)) {
                    errs.push_back("file path");
                }
                break;
            default: break;
        }
    }
    return (/* 0 != day && */ 0 != part && !input_file.empty() && errs.empty());
}

bool ArgParse::setInt(const char *str, const size_t min_size, const size_t max_size, size_t &num) {
    try {
        num = std::atoi(str);
    } catch (std::invalid_argument &) {
        return false;
    }
    if (max_size < num || min_size > num) {
        return false;
    }
    return true;
}

void ArgParse::showErrors() {
    std::cout << "Not acceptable input:\n";
    for (auto err : errs) {
        std::cout << "Invalid/missing " << err << ".\n";
    }
}
} // namespace aoc
