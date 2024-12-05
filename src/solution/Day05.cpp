
#include "solution/Day05.h"
#include <set>
#include <sstream>

namespace aoc {

std::string Day05::part1(const std::vector<std::string> &lines) {
    size_t acc{};
    auto const &order_rules = getOrderRules(lines);
    for (const auto &page_list : getPages(lines)) {
        if (verifyPages(page_list, order_rules)) {
            acc += page_list.at(page_list.size() / 2);
        }
    }
    return std::to_string(acc);
}

std::string Day05::part2(const std::vector<std::string> &lines) {
    size_t acc{};
    const auto &order_rules = getOrderRules(lines);
    for (const auto &page_list : getPages(lines)) {
        if (!verifyPages(page_list, order_rules)) {
            acc += fixPages(page_list, order_rules);
        }
    }
    return std::to_string(acc);
}

std::map<size_t, std::set<size_t>> Day05::getOrderRules(
    const std::vector<std::string> &lines) {
    std::map<size_t, std::set<size_t>> ret{};
    for (auto iter = lines.begin(); !iter->empty(); ++iter) {
        const size_t left = std::stoi(iter->substr(0, 2));
        const size_t right = std::stoi(iter->substr(3, 2));
        ret[left].insert(right);
    }
    return ret;
}

std::vector<std::vector<size_t>> Day05::getPages(const std::vector<std::string> &lines) {
    auto iter = lines.begin();
    while (!iter->empty()) {
        ++iter;
    }
    std::vector<std::vector<size_t>> ret{};
    std::vector<size_t> vec{};
    while (lines.end() != ++iter) {
        std::stringstream str(*iter);
        std::string num{};
        while (getline(str, num, ',')) {
            vec.push_back(std::stoi(num));
        }
        ret.push_back(std::move(vec));
        vec.clear();
    }
    return ret;
}

bool Day05::verifyPages(
    const std::vector<size_t> &pages, const std::map<size_t, std::set<size_t>> &rules) {
    std::set<size_t> prev{};
    for (size_t page : pages) {
        if (rules.contains(page)) {
            for (const size_t after : rules.at(page)) {
                if (prev.contains(after)) {
                    return false;
                }
            }
        }
        prev.insert(page);
    }
    return true;
}

size_t Day05::fixPages(
    const std::vector<size_t> &pages, const std::map<size_t, std::set<size_t>> &order_rules) {

    std::vector<size_t> correct{};

    for (const size_t page : pages) {
        correct.push_back(page);
        size_t idx = correct.size() - 1;
        while (!verifyPages(correct, order_rules)) {
            std::swap(correct[idx - 1], correct[idx]);
            --idx;
        }
    }
    return correct.at(correct.size() / 2);
}
} // namespace aoc
