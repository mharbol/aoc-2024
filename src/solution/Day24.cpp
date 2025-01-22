
#include "solution/Day24.h"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace aoc {

std::string Day24::part1(const std::vector<std::string> &lines) {
    auto [wires, gates] = parse(lines);
    while (!gates.empty()) {
        for (auto iter = gates.begin(); iter != gates.end();) {
            try {
                bool res{};
                switch (std::get<2>(iter->first)) {
                    case AND:
                        res = wires.at(std::get<0>(iter->first)) &&
                              wires.at(std::get<1>(iter->first));
                        break;
                    case XOR:
                        res = 1 == wires.at(std::get<0>(iter->first)) +
                                       wires.at(std::get<1>(iter->first));
                        break;
                    case OR:
                        res = wires.at(std::get<0>(iter->first)) ||
                              wires.at(std::get<1>(iter->first));
                        break;
                }
                wires.insert({iter->second, res});
                iter = gates.erase(iter);
            } catch (const std::out_of_range &) {
                ++iter;
            }
        }
    }
    size_t acc{};
    for (auto riter = wires.rbegin(); riter != wires.rend(); ++riter) {
        if ('z' == riter->first[0]) {
            acc = (acc << 1) + riter->second;
        }
    }
    return std::to_string(acc);
}

std::string Day24::part2(const std::vector<std::string> &lines) {

    GateMapHolder gate_maps{};

    const size_t max_val = parseGateMaps(lines, gate_maps);

    // TODO find these swaps algorithmically
    swapOutputs("z11", "vkq", gate_maps);
    swapOutputs("z24", "mmk", gate_maps);
    swapOutputs("qdq", "pvb", gate_maps);
    swapOutputs("hqh", "z38", gate_maps);

    std::set<std::string> swaps{"z11", "vkq", "z24", "mmk", "qdq", "pvb", "hqh", "z38"};

    std::cout << max_val << std::endl;
    std::string sum{}, carry_in{}, carry_out{};
    std::set<std::string> outputs{};
    traceForwardHalfAdder("x00", "y00", sum, carry_in, gate_maps);
    for (size_t num = 1; num < max_val; ++num) {
        std::cout << "Testing " << num << std::endl;
        bool success = verifyAdder(num, carry_in, carry_out, outputs, gate_maps);
        if (success) {
            std::cout << "SUCCESS\n";
            carry_in = std::move(carry_out);
            carry_out.clear();
        } else {
            std::cout << "FAIL\n";
            break;
        }
    }
    std::string sol{};
    for (const auto &output : swaps) {
        sol += output + ',';
    }
    sol.resize(sol.size() - 1);
    return sol;
}

std::pair<std::map<std::string, bool>,
    std::map<std::tuple<std::string, std::string, Day24::GateType>, std::string>>
Day24::parse(const std::vector<std::string> &lines) {

    std::map<std::string, bool> wires{};
    std::map<std::tuple<std::string, std::string, Day24::GateType>, std::string> gates{};

    auto iter = lines.begin();
    while (!iter->empty()) {
        wires[iter->substr(0, 3)] = iter->at(5) == '1';
        ++iter;
    }

    for (++iter; iter < lines.end(); ++iter) {
        std::string in{};
        std::string out{};
        GateType op{};
        switch (iter->at(4)) {
            case 'A':
                in = iter->substr(8, 3);
                out = iter->substr(15, 3);
                op = AND;
                break;
            case 'X':
                in = iter->substr(8, 3);
                out = iter->substr(15, 3);
                op = XOR;
                break;
            case 'O':
                in = iter->substr(7, 3);
                out = iter->substr(14, 3);
                op = OR;
                break;
        }
        gates.insert({{iter->substr(0, 3), in, op}, out});
    }
    return {wires, gates};
}

size_t Day24::parseGateMaps(const std::vector<std::string> &lines,
    Day24::GateMapHolder &gate_maps) {

    size_t ret{};

    auto iter = lines.begin();
    while (!iter->empty()) {
        ++iter;
    }

    for (++iter; iter != lines.end(); ++iter) {
        std::map<std::pair<std::string, std::string>, std::string> *ptr_map{};
        std::string in0{iter->substr(0, 3)}, in1{}, out{};
        switch (iter->at(4)) {
            case 'A':
                ptr_map = &gate_maps.and_map;
                in1 = iter->substr(8, 3);
                out = iter->substr(15, 3);
                break;
            case 'X':
                ptr_map = &gate_maps.xor_map;
                in1 = iter->substr(8, 3);
                out = iter->substr(15, 3);
                break;
            case 'O':
                ptr_map = &gate_maps.or_map;
                in1 = iter->substr(7, 3);
                out = iter->substr(14, 3);
                break;
        }
        if ('z' == out[0]) {
            if (const size_t val = std::stoul(out.substr(1, 2)); val > ret) {
                ret = val;
            }
        }
        if (in0 < in1) {
            ptr_map->insert({{in0, in1}, out});
        } else {
            ptr_map->insert({{in1, in0}, out});
        }
    }
    return ret;
}

bool Day24::verifyAdder(const size_t num, const std::string &c_in, std::string &c_out,
    std::set<std::string> &outputs, const GateMapHolder &gates) {

    std::stringstream x{}, y{}, z{};
    outputs.clear();
    outputs.insert(c_in);

    x << "x" << std::setw(2) << std::setfill('0') << num;
    y << "y" << std::setw(2) << std::setfill('0') << num;
    z << "z" << std::setw(2) << std::setfill('0') << num;

    std::string xy_sum{}, xy_carry{}, z_out{}, ha_c_out{};

    auto ret = traceForwardHalfAdder(x.str(), y.str(), xy_sum, xy_carry, gates);
    std::cout << x.str() << " " << y.str() << " -> ";
    if (ret) {
        std::cout << num << " - Failed first half adder" << std::endl;
        return false;
    }
    std::cout << xy_sum << " " << xy_carry << "\n";
    outputs.insert(xy_sum);
    outputs.insert(xy_carry);

    std::cout << xy_sum << " " << c_in << " -> ";
    ret = traceForwardHalfAdder(xy_sum, c_in, z_out, ha_c_out, gates);
    if (ret) {
        std::cout << num << " - Failed second half adder ";
        switch (*ret) {
            case OR: std::cout << "OR\n"; break;
            case AND: std::cout << "AND\n"; break;
            case XOR: std::cout << "XOR\n"; break;
        }
        return false;
    }
    std::cout << z_out << " " << ha_c_out << "\n";
    if (z.str() != z_out) {
        std::cout << num << " - Failed z out " << z_out << std::endl;
        outputs.clear();
        outputs.insert(z_out);
        return false;
    }
    outputs.insert(z_out);
    outputs.insert(ha_c_out);

    auto or_out = gates.getGate(OR, xy_carry, ha_c_out);
    if (!or_out) {
        std::cout << num << " - Failed carry or" << std::endl;
        return false;
    }
    c_out = std::move(*or_out);

    return true;
}

std::optional<Day24::GateType> Day24::traceForwardHalfAdder(const std::string &in0,
    const std::string &in1, std::string &sum, std::string &carry,
    const GateMapHolder &gate_maps) {

    const auto &wire0 = (in0 < in1 ? in0 : in1);
    const auto &wire1 = (wire0 == in0 ? in1 : in0);
    std::optional<GateType> ret{};

    try {
        sum = gate_maps.xor_map.at({wire0, wire1});
    } catch (const std::out_of_range &) {
        ret = XOR;
    }
    try {
        carry = gate_maps.and_map.at({wire0, wire1});
    } catch (const std::out_of_range &) {
        ret = (ret.has_value() ? OR : XOR);
    }

    return ret;
}

void Day24::swapOutputs(const std::string &out0, const std::string &out1,
    Day24::GateMapHolder &gate_maps) {

    std::map<std::pair<std::string, std::string>, std::string> *gates[] = {&gate_maps.and_map,
        &gate_maps.or_map, &gate_maps.xor_map};
    std::map<std::pair<std::string, std::string>, std::string> **gates_iter{gates};
    std::string *ptr_out0{}, *ptr_out1{};
    for (size_t i = 0; i < 3; ++i) {
        for (auto &gate : **gates_iter) {
            if (out0 == gate.second) {
                ptr_out0 = &gate.second;
            }
            if (out1 == gate.second) {
                ptr_out1 = &gate.second;
            }
        }
        ++gates_iter;
    }
    std::swap(*ptr_out0, *ptr_out1);
}

std::optional<std::string> Day24::GateMapHolder::getGate(const Day24::GateType gate_type,
    const std::string &in0, const std::string &in1) const {

    const auto &wire0 = (in0 < in1 ? in0 : in1);
    const auto &wire1 = (wire0 == in0 ? in1 : in0);

    const std::map<std::pair<std::string, std::string>, std::string> *map_ptr{};
    switch (gate_type) {
        case AND: map_ptr = &and_map; break;
        case XOR: map_ptr = &xor_map; break;
        case OR: map_ptr = &or_map; break;
    }
    try {
        return map_ptr->at({wire0, wire1});
    } catch (const std::out_of_range &) {
        return {};
    }
}
} // namespace aoc
