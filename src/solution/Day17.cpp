
#include "solution/Day17.h"
#include <sstream>
#include <string>
#include <vector>

namespace aoc {

std::string Day17::part1(const std::vector<std::string> &lines) {
    auto computer = parse(lines);
    computer.runProgram();
    return computer.getOutput();
}

std::string Day17::part2(const std::vector<std::string> &lines) {
    auto computer = parse(lines);
    return std::to_string(computer.runCheckProgram(0));
}

ElfComputer Day17::parse(const std::vector<std::string> &lines) {

    std::vector<std::size_t> prog{};
    std::stringstream str(lines.at(4).substr(9, lines.at(4).size() - 9));
    std::string code{};
    while (std::getline(str, code, ',')) {
        prog.push_back(std::stoul(code));
    }
    return ElfComputer(std::stoul(lines.at(0).substr(12, lines.at(0).size() - 12)),
        std::stoul(lines.at(1).substr(12, lines.at(1).size() - 12)),
        std::stoul(lines.at(2).substr(12, lines.at(2).size() - 12)), std::move(prog));
}

void ElfComputer::runProgram() {
    do {
        switch (program.at(ip)) {
            case 0: adv(program.at(ip + 1)); break;
            case 1: bxl(program.at(ip + 1)); break;
            case 2: bst(program.at(ip + 1)); break;
            case 3: jnz(program.at(ip + 1)); break;
            case 4: bxc(program.at(ip + 1)); break;
            case 5: out(program.at(ip + 1)); break;
            case 6: bdv(program.at(ip + 1)); break;
            case 7: cdv(program.at(ip + 1)); break;
        }
    } while (ip < program.size());
}

size_t ElfComputer::combo(size_t arg) {
    switch (arg) {
        case 4: return reg_A;
        case 5: return reg_B;
        case 6: return reg_C;
        default: return arg;
    }
}

void ElfComputer::adv(size_t arg) {
    reg_A = reg_A / (1 << combo(arg));
    incIp();
}

void ElfComputer::bdv(size_t arg) {
    reg_B = reg_A / (1 << combo(arg));
    incIp();
}

void ElfComputer::cdv(size_t arg) {
    reg_C = reg_A / (1 << combo(arg));
    incIp();
}

void ElfComputer::bxl(size_t arg) {
    reg_B ^= arg;
    incIp();
}

void ElfComputer::bst(size_t arg) {
    reg_B = combo(arg) & 0b111;
    incIp();
}

void ElfComputer::bxc(size_t /* arg */) {
    reg_B ^= reg_C;
    incIp();
}

void ElfComputer::out(size_t arg) {
    output_buf.push_back(combo(arg) & 0b111);
    incIp();
}

void ElfComputer::jnz(size_t arg) {
    if (0 == reg_A) {
        incIp();
    } else {
        ip = arg;
    }
}

bool ElfComputer::incIp() {
    return (ip += 2) < program.size();
}

std::string ElfComputer::getOutput() const {
    std::string out{};
    for (const auto output : output_buf) {
        out.append(std::to_string(output));
        out.append(",");
    }
    out.resize(out.size() - 1);
    return out;
}

size_t ElfComputer::runCheckProgram(const size_t init_A) {

    for (size_t k = 0; k < 8; ++k) {
        reset(init_A + k);
        runProgram();
        if (checkTailEq()) {
            if (output_buf.size() == program.size()) {
                return init_A + k;
            } else if (size_t ret = runCheckProgram(8 * (init_A + k)); 0 != ret) {
                return ret;
            }
        }
    }
    return 0;
}

bool ElfComputer::checkTailEq() {
    size_t idx = program.size() - output_buf.size();
    auto iter = output_buf.begin();
    while (iter != output_buf.end()) {
        if (program.at(idx) != *iter) {
            return false;
        } else {
            ++iter;
            ++idx;
        }
    }
    return true;
}

void ElfComputer::reset(const size_t init_A) {
    reg_A = init_A;
    reg_B = reg_B_orig;
    reg_C = reg_C_orig;
    ip = 0;
    output_buf.clear();
}
} // namespace aoc
