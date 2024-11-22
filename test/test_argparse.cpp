#include "tools/ArgParse.h"
#include <gtest/gtest.h>

TEST(TestArgParse, TestValidInputs) {
    aoc::ArgParse parser0{};
    const char *argv0[] = {"aoc2024", "-d", "1", "-p", "1", "-f", "../../resources/day00.txt"};
    auto stat = parser0.parseArgs(7, argv0);
    ASSERT_EQ(aoc::ArgParse::Status::OK, stat);
    ASSERT_EQ(1, parser0.getDay());
    ASSERT_EQ(1, parser0.getPart());

    aoc::ArgParse parser1{};
    const char *argv1[] = {
        "aoc2024", "-p", "2", "-f", "../../resources/day00.txt", "-d", "25"};
    stat = parser1.parseArgs(7, argv1);
    ASSERT_EQ(aoc::ArgParse::Status::OK, stat);
    ASSERT_EQ(25, parser1.getDay());
    ASSERT_EQ(2, parser1.getPart());
}

TEST(TestArgParse, TestHelpMessage) {
    aoc::ArgParse parser{};
    const char *argv0[] = {"aoc2024", "-h"};
    auto stat = parser.parseArgs(2, argv0);
    ASSERT_EQ(aoc::ArgParse::Status::HELP, stat);
}

TEST(TestArgParse, TestInvalidInputs) {
    aoc::ArgParse parser0{};
    const char *argv0[] = {
        "aoc2024", "-d", "26", "-p", "1", "-f", "../../resources/day00.txt"};
    auto stat = parser0.parseArgs(7, argv0);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Day must be between 1 and 25.", parser0.getErrorMsg());

    aoc::ArgParse parser1{};
    const char *argv1[] = {
        "aoc2024", "-d", "-3", "-p", "1", "-f", "../../resources/day00.txt"};
    stat = parser1.parseArgs(7, argv1);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Day must be between 1 and 25.", parser1.getErrorMsg());

    aoc::ArgParse parser2{};
    const char *argv2[] = {"aoc2024", "-d", "4", "-p", "3", "-f", "../../resources/day00.txt"};
    stat = parser2.parseArgs(7, argv2);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Part must be between 1 and 2.", parser2.getErrorMsg());

    aoc::ArgParse parser3{};
    const char *argv3[] = {"aoc2024", "-d", "4", "-p", "0", "-f", "../../resources/day00.txt"};
    stat = parser3.parseArgs(7, argv3);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Part must be between 1 and 2.", parser3.getErrorMsg());

    aoc::ArgParse parser4{};
    const char *argv4[] = {"aoc2024", "-d", "a", "-p", "0", "-f", "../../resources/day00.txt"};
    stat = parser4.parseArgs(7, argv4);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Invalid input after '-d': a", parser4.getErrorMsg());

    aoc::ArgParse parser5{};
    const char *argv5[] = {"aoc2024", "-d", "4", "-p", "x", "-f", "../../resources/day00.txt"};
    stat = parser5.parseArgs(7, argv5);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Invalid input after '-p': x", parser5.getErrorMsg());

    aoc::ArgParse parser6{};
    const char *argv6[] = {"aoc2024", "-d", "4", "-p", "2", "-f", "../../resources/dne.txt"};
    stat = parser6.parseArgs(7, argv6);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Could not find input file '../../resources/dne.txt'.", parser6.getErrorMsg());
}

TEST(TestArgParse, TestIncomplete) {
    aoc::ArgParse parser0{};
    const char *argv0[] = {"aoc2024", "-d", "4", "-f", "../../resources/day00.txt"};
    auto stat = parser0.parseArgs(5, argv0);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Did not get full input.", parser0.getErrorMsg());

    aoc::ArgParse parser1{};
    const char *argv1[] = {"aoc2024", "-d", "4", "-p", "1"};
    stat = parser1.parseArgs(5, argv1);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Did not get full input.", parser1.getErrorMsg());

    aoc::ArgParse parser2{};
    const char *argv2[] = {"aoc2024", "-p", "1", "-f", "../../resources/day00.txt"};
    stat = parser2.parseArgs(5, argv2);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Did not get full input.", parser2.getErrorMsg());

    aoc::ArgParse parser3{};
    const char *argv3[] = {"aoc2024", "-p"};
    stat = parser3.parseArgs(2, argv3);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Expected part number after '-p'.", parser3.getErrorMsg());

    aoc::ArgParse parser4{};
    const char *argv4[] = {"aoc2024", "-d"};
    stat = parser4.parseArgs(2, argv4);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Expected day number after '-d'.", parser4.getErrorMsg());

    aoc::ArgParse parser5{};
    const char *argv5[] = {"aoc2024", "-f"};
    stat = parser5.parseArgs(2, argv5);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Expected input file after '-f'.", parser5.getErrorMsg());
}

TEST(TestArgParse, TestMultiple) {
    aoc::ArgParse parser0{};
    const char *argv0[] = {
        "aoc2024", "-f", "../../resources/day00.txt", "-f", "../../resources/day01.txt"};
    auto stat = parser0.parseArgs(5, argv0);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Cannot specify more than one input file.", parser0.getErrorMsg());

    aoc::ArgParse parser1{};
    const char *argv1[] = {"aoc2024", "-d", "3", "-d", "4"};
    stat = parser1.parseArgs(5, argv1);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Cannot specify more than one day.", parser1.getErrorMsg());

    aoc::ArgParse parser2{};
    const char *argv2[] = {"aoc2024", "-p", "1", "-p", "2"};
    stat = parser2.parseArgs(5, argv2);
    ASSERT_EQ(stat, aoc::ArgParse::Status::FAIL);
    ASSERT_EQ("Cannot specify more than one part.", parser2.getErrorMsg());
}
