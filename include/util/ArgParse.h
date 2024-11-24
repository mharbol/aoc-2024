
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
     * Return status for parseArgs.
     */
    enum Status { HELP, OK, FAIL };

    /**
     * Parse the arguments as they are passed into `main()`.
     * @param argc number of arguments
     * @param argv the array of arguments
     * @return status indicating the parser's result
     */
    Status parseArgs(const int argc, const char **const argv) noexcept;

    /**
     * Displays the usage of this application to the console.
     */
    void showUsage() const;

    /**
     * Displays the usage and help message to the console.
     */
    void showHelp() const;

    ArgParse() = default;
    ~ArgParse() = default;

private:
    void processDay(size_t &idx, const std::vector<std::string> &args);
    void processPart(size_t &idx, const std::vector<std::string> &args);
    void processFile(size_t &idx, const std::vector<std::string> &args);
    std::string err{};
    std::string input_file{};
    int32_t day{99};
    int32_t part{99};
    static const std::string usage;
    static const std::string help_msg;

    // indicate that this value  has already been set
    bool help_flag{}, day_flag{}, part_flag{}, file_flag{};

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

    inline std::string &getErrorMsg() {
        return err;
    }
};
} // namespace aoc

#endif
