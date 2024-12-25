
#ifndef __AOC_DAY_17_H__
#define __AOC_DAY_17_H__

#include "Solution.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace aoc {

struct ElfComputer {
    size_t reg_A{}, reg_B{}, reg_C{};
    size_t ip{};
    std::vector<size_t> program{};
    std::vector<size_t> output_buf{};
    bool incIp();

    ElfComputer(size_t reg_A, size_t reg_B, size_t reg_C, std::vector<size_t> &&program)
        : reg_A(reg_A), reg_B(reg_B), reg_C(reg_C), program(program) {

        reg_A_orig = reg_A;
        reg_B_orig = reg_B;
        reg_C_orig = reg_C;
    }
    ~ElfComputer() = default;

    std::string getOutput() const;
    size_t combo(size_t arg);

    void adv(size_t arg);
    void bdv(size_t arg);
    void cdv(size_t arg);
    void bxl(size_t arg);
    void bst(size_t arg);
    void jnz(size_t arg);
    void bxc(size_t arg);
    void out(size_t arg);

    void runProgram();
    size_t runCheckProgram(const size_t init_A);
    void reset(const size_t init_A);

private:
    bool checkTailEq();
    size_t reg_A_orig{}, reg_B_orig{}, reg_C_orig{};
};

class Day17 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    ElfComputer parse(const std::vector<std::string> &lines);
};
} // namespace aoc
#endif
