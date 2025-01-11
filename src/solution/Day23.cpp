
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
    std::unordered_map<std::string, std::unordered_set<std::string>> net_map{};
    std::set<std::string> R{}, ret{};
    std::unordered_set<std::string> P{}, X{};
    for (const auto &line : lines) {
        const std::string node0 = line.substr(0, 2);
        const std::string node1 = line.substr(3, 2);
        net_map[node0].insert(node1);
        net_map[node1].insert(node0);
        P.insert(node0);
        P.insert(node1);
    }
    bronKerboschPivot(R, P, X, net_map, ret);
    std::string password{};
    for (const auto &comp_name : ret) { // std::set is ordered
        password += comp_name + ',';
    }
    password.resize(password.size() - 1);
    return password;
}

void Day23::bronKerboschPivot(std::set<std::string> &R, std::unordered_set<std::string> &P,
    std::unordered_set<std::string> &X,
    const std::unordered_map<std::string, std::unordered_set<std::string>> &graph,
    std::set<std::string> &ret) {

    if (P.empty() && X.empty()) {
        if (ret.size() < R.size()) {
            ret = std::move(R);
        }
        return;
    }

    // select pivot to minimize recursions (most neighbors)
    std::string pivot{};
    size_t max_neighbors{};
    for (const auto &node : P) {
        if (node.size() > max_neighbors) {
            max_neighbors = node.size();
            pivot = node;
        }
    }
    for (const auto &node : X) {
        if (node.size() > max_neighbors) {
            max_neighbors = node.size();
            pivot = node;
        }
    }

    for (auto v_iter = P.begin(); v_iter != P.end();) {
        if (graph.at(pivot).contains(*v_iter)) {
            ++v_iter;
            continue;
        }
        auto R_union_v = R;
        R_union_v.insert(*v_iter);
        std::unordered_set<std::string> P_int_N_v{};
        for (const auto &node : P) {
            if (graph.at(*v_iter).contains(node)) {
                P_int_N_v.insert(node);
            }
        }
        std::unordered_set<std::string> X_int_N_v{};
        for (const auto &node : X) {
            if (graph.at(*v_iter).contains(node)) {
                X_int_N_v.insert(node);
            }
        }
        bronKerboschPivot(R_union_v, P_int_N_v, X_int_N_v, graph, ret);
        X.insert(*v_iter);
        v_iter = P.erase(v_iter);
    }
}
} // namespace aoc
