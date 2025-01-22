
#ifndef __AOC_DAY_24_H__
#define __AOC_DAY_24_H__

#include "Solution.h"
#include <cstddef>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <utility>

namespace aoc {
class Day24 : public Solution {
public:
    std::string part1(const std::vector<std::string> &lines) override;
    std::string part2(const std::vector<std::string> &lines) override;

private:
    enum GateType { AND, OR, XOR };
    struct GateMapHolder {
        std::map<std::pair<std::string, std::string>, std::string> and_map{};
        std::map<std::pair<std::string, std::string>, std::string> xor_map{};
        std::map<std::pair<std::string, std::string>, std::string> or_map{};
        std::optional<std::string> getGate(const GateType gate_type, const std::string &in0,
            const std::string &in1) const;
    };

    std::pair<std::map<std::string, bool>,
        std::map<std::tuple<std::string, std::string, GateType>, std::string>>
    parse(const std::vector<std::string> &lines);
    size_t parseGateMaps(const std::vector<std::string> &lines, GateMapHolder &gate_maps);

    // Returns which gate (if any) does not exist for the given in wires.
    // OR is used to represent both gates missing.
    std::optional<GateType> traceForwardHalfAdder(const std::string &in0,
        const std::string &in1, std::string &sum, std::string &carry,
        const GateMapHolder &gate_maps);
    bool verifyAdder(const size_t num, const std::string &c_in, std::string &c_out,
        std::set<std::string> &outputs, const GateMapHolder &gates);
    void swapOutputs(const std::string &out0, const std::string &out1,
        GateMapHolder &gate_maps);
};
} // namespace aoc
#endif
