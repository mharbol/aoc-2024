
#include "tools/ArgParse.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace aoc {

const std::string ArgParse::usage{"Usage: aoc2024 -d <day> -p <part> -f <file>\n"
                                  "      (solve a particular problem)\n"
                                  "   or  aoc2024 -h\n"
                                  "      (to display help message)\n"};

const std::string ArgParse::help_msg{"-d   Day's problem to test, 1-25.\n"
                                     "-p   Part to solve, 1 or 2\n"
                                     "-f   Path to problem input file\n"};

ArgParse::Status ArgParse::parseArgs(const int argc, const char **const argv) noexcept {

    std::vector<std::string> args{};
    for (int idx = 0; idx < argc; ++idx) {
        args.push_back(std::string(argv[idx]));
    }

    for (size_t idx = 1; idx < args.size(); ++idx) {
        std::string &arg = args.at(idx);
        if ("-h" == arg) {
            help_flag = true;
        } else if ("-d" == arg) {
            processDay(idx, args);
        } else if ("-p" == arg) {
            processPart(idx, args);
        } else if ("-f" == arg) {
            processFile(idx, args);
        } else {
            err = "Unrecognized argument: '" + arg + "'.";
        }
        if (!err.empty()) {
            return Status::FAIL;
        }
    }
    if (help_flag) {
        return Status::HELP;
    }
    if (!day_flag || !part_flag || !file_flag) {
        err = "Did not get full input.";
        return Status::FAIL;
    }
    return Status::OK;
}

void ArgParse::processDay(size_t &idx, const std::vector<std::string> &args) {
    if (day_flag) {
        err = "Cannot specify more than one day.";
        return;
    }
    try {
        day_flag = true;
        day = std::stoi(args.at(++idx));
        if (0 > day || 25 < day) {
            err = "Day must be between 1 and 25.";
        }
    } catch (const std::invalid_argument &) {
        err = "Invalid input after '-d': " + args.at(idx);
    } catch (const std::out_of_range &) {
        err = "Expected day number after '-d'.";
    }
}

void ArgParse::processPart(size_t &idx, const std::vector<std::string> &args) {
    if (part_flag) {
        err = "Cannot specify more than one part.";
        return;
    }
    try {
        part_flag = true;
        part = std::stoi(args.at(++idx));
        if (1 > part || 2 < part) {
            err = "Part must be between 1 and 2.";
        }
    } catch (const std::invalid_argument &) {
        err = "Invalid input after '-p': " + args.at(idx);
    } catch (const std::out_of_range &) {
        err = "Expected part number after '-p'.";
    }
}

void ArgParse::processFile(size_t &idx, const std::vector<std::string> &args) {
    if (file_flag) {
        err = "Cannot specify more than one input file.";
        return;
    }
    try {
        file_flag = true;
        input_file = args.at(++idx);
        if (!std::filesystem::exists(input_file)) {
            err = "Could not find input file '" + input_file + "'.";
        }
    } catch (const std::out_of_range &) {
        err = "Expected input file after '-f'";
    }
}

void ArgParse::showHelp() const {
    std::cout << usage << '\n' << help_msg;
}

void ArgParse::showUsage() const {
    std::cout << usage;
}
} // namespace aoc
