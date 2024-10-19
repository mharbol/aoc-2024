
#include "tools/fileread.h"
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> aoc::readInput(const std::string &file_path) noexcept {
    std::ifstream file(file_path);
    std::vector<std::string> ret;
    std::string line;
    while (std::getline(file, line)) {
        ret.push_back(std::move(line));
    }
    file.close();
    return ret;
}
