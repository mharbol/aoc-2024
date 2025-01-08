
#include "solution/Day23.h"
#include <map>
#include <set>
#include <utility>

namespace aoc {

std::string Day23::part1(const std::vector<std::string> &lines) {
    std::map<std::string, std::set<std::string>> net_map{};
    for (const auto &line : lines) {
        const std::string node0 = line.substr(0, 2);
        const std::string node1 = line.substr(3, 2);
        net_map[node0].insert(node1);
        net_map[node1].insert(node0);
    }
    std::set<std::set<std::string>> cycles3{};
    for (const auto &[node, neighbors] : net_map) {
        for (auto n0 = neighbors.begin(); n0 != neighbors.end(); ++n0) {
            auto n1 = n0;
            while (++n1 != neighbors.end()) {
                if (net_map[*n0].contains(*n1)) {
                    cycles3.insert({node, *n0, *n1});
                }
            }
        }
    }
    size_t acc{};
    for (const auto &cycle : cycles3) {
        for (const auto &node : cycle) {
            if ('t' == node[0]) {
                ++acc;
                break;
            }
        }
    }
    return std::to_string(acc);
}

std::string Day23::part2(const std::vector<std::string> &lines) {
    std::map<std::string, std::set<std::string>> net_map{};
    std::set<std::string> P{}, R{}, X{}, ret{};
    for (const auto &line : lines) {
        const std::string node0 = line.substr(0, 2);
        const std::string node1 = line.substr(3, 2);
        net_map[node0].insert(node1);
        net_map[node1].insert(node0);
        P.insert(node0);
        P.insert(node1);
    }
    bronKerbosch(R, P, X, net_map, ret);
    std::string password{};
    for (const auto &comp_name : ret) { // std::set is ordered
        password += comp_name + ',';
    }
    password.resize(password.size() - 1);
    return password;
}

void Day23::bronKerbosch(std::set<std::string> &R, std::set<std::string> &P,
    std::set<std::string> &X, const std::map<std::string, std::set<std::string>> &graph,
    std::set<std::string> &ret) {

    if (P.empty() && X.empty()) {
        if (ret.size() < R.size()) {
            ret = std::move(R);
        }
        return;
    }

    for (auto v = P.begin(); v != P.end();) {
        auto RUv = R;
        RUv.insert(*v);
        std::set<std::string> neighbor_set_P_v{};
        for (const auto &u : P) {
            if (graph.at(*v).contains(u)) {
                neighbor_set_P_v.insert(u);
            }
        }
        std::set<std::string> neighbor_set_X_v{};
        for (const auto &u : X) {
            if (graph.at(*v).contains(u)) {
                neighbor_set_X_v.insert(u);
            }
        }
        bronKerbosch(RUv, neighbor_set_P_v, neighbor_set_X_v, graph, ret);
        X.insert(*v);
        v = P.erase(v);
    }
}
} // namespace aoc
