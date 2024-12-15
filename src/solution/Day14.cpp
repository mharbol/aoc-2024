
#include "solution/Day14.h"
#include <cstdint>
#include <set>
#include <string>
#include <vector>

namespace aoc {

std::string Day14::part1(const std::vector<std::string> &lines) {
    HEIGHT = 103;
    WIDTH = 101;
    auto robots = parse(lines);
    for (auto &robot : robots) {
        robot.teleport(100, WIDTH, HEIGHT);
    }
    return std::to_string(prodQuad(robots));
}

std::string Day14::part2(const std::vector<std::string> &lines) {
    HEIGHT = 103;
    WIDTH = 101;
    const int32_t SURROUND = 30;
    size_t count{};
    auto robots = parse(lines);
    while (true) {
        std::set<std::pair<int32_t, int32_t>> robogrid{};
        for (auto &robot : robots) {
            robot.teleport(1, WIDTH, HEIGHT);
            robogrid.emplace(robot.p_row, robot.p_col);
        }
        ++count;
        if (SURROUND <= countSurrounded(robogrid)) {
            break;
        }
    }
    return std::to_string(count);
}

std::vector<Robot> Day14::parse(const std::vector<std::string> &lines) {

    std::vector<Robot> ret{};

    for (const auto &line : lines) {
        const size_t comma_pos_1 = line.find(',');
        const size_t comma_pos_2 = line.find(',', comma_pos_1 + 1);
        const size_t v_pos = line.find('v');
        const int32_t px = std::stoi(line.substr(2, comma_pos_1 - 1));
        const int32_t py = std::stoi(line.substr(comma_pos_1 + 1, v_pos - comma_pos_1 - 1));
        const int32_t vx = std::stoi(line.substr(v_pos + 2, comma_pos_2 - v_pos - 1));
        const int32_t vy = std::stoi(line.substr(comma_pos_2 + 1, line.size() - comma_pos_2));
        ret.emplace_back(py, px, vy, vx);
    }
    return ret;
}

size_t Day14::prodQuad(const std::vector<Robot> &robots) {

    size_t q1{}, q2{}, q3{}, q4{};
    for (const auto &robot : robots) {
        if (robot.p_row < HEIGHT / 2) {
            if (robot.p_col < WIDTH / 2) {
                ++q2;
            } else if (robot.p_col > WIDTH / 2) {
                ++q1;
            }
        } else if (robot.p_row > HEIGHT / 2) {
            if (robot.p_col < WIDTH / 2) {
                ++q3;
            } else if (robot.p_col > WIDTH / 2) {
                ++q4;
            }
        }
    }
    return q1 * q2 * q3 * q4;
}

size_t Day14::countSurrounded(const std::set<std::pair<int32_t, int32_t>> &robogrid) {
    size_t count{};
    for (const auto &robopair : robogrid) {
        if (robogrid.contains({robopair.first, robopair.second + 1}) &&
            robogrid.contains({robopair.first, robopair.second - 1}) &&
            robogrid.contains({robopair.first + 1, robopair.second}) &&
            robogrid.contains({robopair.first - 1, robopair.second})) {

            ++count;
        }
    }
    return count;
}

void Robot::teleport(int32_t seconds, int32_t width, int32_t height) {
    p_row += seconds * v_row;
    p_row %= height;
    p_row += p_row < 0 ? height : 0;
    p_col += seconds * v_col;
    p_col %= width;
    p_col += p_col < 0 ? width : 0;
}
} // namespace aoc
