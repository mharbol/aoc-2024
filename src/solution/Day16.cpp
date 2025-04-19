
#include "solution/Day16.h"

namespace aoc {

std::string Day16::part1(const std::vector<std::string> &lines) {
    return std::to_string(lowestReindeer(lines));
}

std::string Day16::part2(const std::vector<std::string> &lines) {
    const size_t target = lowestReindeer(lines);
    auto [end_row, end_col, start] = getStartEnd(lines);
    start.frame_id = 1;
    size_t frame_id = 1;
    std::map<std::pair<size_t, size_t>, size_t> visited_scores{};
    std::map<size_t, std::set<std::pair<size_t, size_t>>> frame_history{};
    std::map<size_t, size_t> frame_parent_assoc{};
    std::priority_queue<MazeFrame, std::vector<MazeFrame>, std::greater<MazeFrame>> pq{};
    std::set<std::pair<size_t, size_t>> successful_visits{};

    frame_parent_assoc[frame_id] = 0;
    successful_visits.emplace(start.row, start.col);

    pq.push(start);
    while (pq.top().score <= target) {
        MazeFrame frame = pq.top();
        pq.pop();
        if (end_row == frame.row && end_col == frame.col) {
            size_t id = frame.frame_id;
            while (0 != id) {
                for (auto &pr : frame_history[id]) {
                    successful_visits.insert(pr);
                }
                id = frame_parent_assoc[id];
            }
        } else {
            frame.branchJunction(lines, visited_scores, frame_history, frame_parent_assoc, pq,
                target, frame_id);
        }
    }

    return std::to_string(successful_visits.size());
}

std::tuple<size_t, size_t, MazeFrame> Day16::getStartEnd(
    const std::vector<std::string> &lines) {

    MazeFrame ret_frame{};
    size_t end_row{}, end_col{};
    for (size_t row = 0; row < lines.size(); ++row) {
        for (size_t col = 0; col < lines.at(row).size(); ++col) {
            if ('E' == lines.at(row).at(col)) {
                end_row = row;
                end_col = col;
            } else if ('S' == lines.at(row).at(col)) {
                ret_frame.row = row;
                ret_frame.col = col;
            }
        }
    }
    return {end_row, end_col, ret_frame};
}

void MazeFrame::stepToBranch(const std::vector<std::string> &lines,
    std::unordered_set<std::tuple<size_t, size_t, int32_t, int32_t>> &visited,
    std::priority_queue<MazeFrame, std::vector<MazeFrame>, std::greater<MazeFrame>> &pq) {

    const auto here = std::make_tuple(row, col, dr, dc);
    if (visited.contains(here)) {
        return;
    }
    visited.insert(std::move(here));

    while ('#' != lines.at(row).at(col)) {
        if ('E' == lines.at(row).at(col)) {
            pq.emplace(row, col, dr, dc, score);
            return;
        }
        if (0 == dr) {
            if ('.' == lines.at(row + 1).at(col)) {
                pq.emplace(row, col, 1, 0, score + 1000);
            }
            if ('.' == lines.at(row - 1).at(col)) {
                pq.emplace(row, col, -1, 0, score + 1000);
            }
        } else {
            if ('.' == lines.at(row).at(col + 1)) {
                pq.emplace(row, col, 0, 1, score + 1000);
            }
            if ('.' == lines.at(row).at(col - 1)) {
                pq.emplace(row, col, 0, -1, score + 1000);
            }
        }
        row += dr;
        col += dc;
        ++score;
    }
}

void MazeFrame::branchJunction(const std::vector<std::string> &lines,
    std::map<std::pair<size_t, size_t>, size_t> &visited_scores,
    std::map<size_t, std::set<std::pair<size_t, size_t>>> &frame_history,
    std::map<size_t, size_t> &frame_parent_assoc,
    std::priority_queue<MazeFrame, std::vector<MazeFrame>, std::greater<MazeFrame>> &pq,
    const size_t target, size_t &new_frame_id) {

    const auto here = std::make_pair(row, col);
    if (visited_scores.contains(here)) {
        if (visited_scores.at(here) < score) {
            return;
        }
    }
    visited_scores[here] = score;

    while ('#' != lines.at(row).at(col) && score <= target) {
        frame_history[frame_id].emplace(row, col);
        if ('E' == lines.at(row).at(col)) {
            pq.emplace(row, col, 0, 0, score, frame_id, parent_id);
            return;
        }
        if (0 == dr) {
            if ('.' == lines.at(row + 1).at(col)) {
                pq.emplace(row + 1, col, 1, 0, score + 1001, ++new_frame_id, frame_id);
                frame_parent_assoc[new_frame_id] = frame_id;
                frame_parent_assoc[++new_frame_id] = frame_id;
                frame_id = new_frame_id;
            }
            if ('.' == lines.at(row - 1).at(col)) {
                pq.emplace(row - 1, col, -1, 0, score + 1001, ++new_frame_id, frame_id);
                frame_parent_assoc[new_frame_id] = frame_id;
                frame_parent_assoc[++new_frame_id] = frame_id;
                frame_id = new_frame_id;
            }
        } else {
            if ('.' == lines.at(row).at(col + 1)) {
                pq.emplace(row, col + 1, 0, 1, score + 1001, ++new_frame_id, frame_id);
                frame_parent_assoc[new_frame_id] = frame_id;
                frame_parent_assoc[++new_frame_id] = frame_id;
                frame_id = new_frame_id;
            }
            if ('.' == lines.at(row).at(col - 1)) {
                pq.emplace(row, col - 1, 0, -1, score + 1001, ++new_frame_id, frame_id);
                frame_parent_assoc[new_frame_id] = frame_id;
                frame_parent_assoc[++new_frame_id] = frame_id;
                frame_id = new_frame_id;
            }
        }
        row += dr;
        col += dc;
        ++score;
    }
}

size_t Day16::lowestReindeer(const std::vector<std::string> &lines) {
    const auto [end_row, end_col, start] = getStartEnd(lines);
    std::priority_queue<MazeFrame, std::vector<MazeFrame>, std::greater<MazeFrame>> pq{};
    std::unordered_set<std::tuple<size_t, size_t, int32_t, int32_t>> visited{};

    pq.push(start);
    while (end_row != pq.top().row || end_col != pq.top().col) {
        MazeFrame frame = pq.top();
        pq.pop();
        frame.stepToBranch(lines, visited, pq);
    }
    return pq.top().score;
}
} // namespace aoc
