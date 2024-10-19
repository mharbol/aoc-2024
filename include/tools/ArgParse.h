
#ifndef __AOC_ARGPARSE_H__
#define __AOC_ARGPARSE_H__

#include <cstddef>
#include <string>
#include <vector>
namespace aoc {
class ArgParse {
public:
    ArgParse() = default;
    ~ArgParse() = default;

    bool parseArgs(int argc, char **argv) noexcept;
    void showErrors();

private:
    bool setInt(const char *str, const size_t min_size, const size_t max_size, size_t &num);
    std::vector<std::string> errs{};
    std::string input_file{};
    size_t day{};
    size_t part{};

public:
    inline size_t getDay() const {
        return day;
    }
    inline size_t getPart() const {
        return part;
    }
    inline std::string getFilePath() const {
        return input_file;
    }
};
} // namespace aoc

#endif
