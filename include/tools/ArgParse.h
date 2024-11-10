
#ifndef __AOC_ARGPARSE_H__
#define __AOC_ARGPARSE_H__

#include <cstddef>
#include <string>
#include <vector>
namespace aoc {
/**
 * Argument parser for this application.
 */
class ArgParse {
public:
    /**
     * Parse the arguments as they are passed into `main()`.
     * @param argc number of arguments
     * @param argv the array of arguments
     * @return true if parsing was successful otherwise false
     */

    bool parseArgs(int argc, char **argv) noexcept;
    /**
     * Display errors if any. Only effective after a call to `parseArgs()`.
     */
    void showErrors();

    ArgParse() = default;
    ~ArgParse() = default;

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
