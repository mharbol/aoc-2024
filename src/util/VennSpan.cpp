#include "util/VennSpan.h"
#include <cstdint>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

namespace aoc {

template <typename IntegerT>
void VennSpan<IntegerT>::venn(const VennSpan<IntegerT> &v1, const VennSpan<IntegerT> &v2,
    std::vector<VennSpan<IntegerT>> &ex_v1, VennSpan<IntegerT> &common,
    std::vector<VennSpan<IntegerT>> &ex_v2) {

    ex_v1.clear();
    ex_v2.clear();
    common.clear();

    if (v2.start < v1.start) {
        if (v2.end <= v1.start) {
            ex_v1.emplace_back(v1.start, v1.end);
            ex_v2.emplace_back(v2.start, v2.end);
        } else if (v2.end < v1.end) {
            ex_v1.emplace_back(v2.end, v1.end);
            ex_v2.emplace_back(v2.start, v1.start);
            common = VennSpan<IntegerT>(v1.start, v2.end);
        } else if (v2.end == v1.end) {
            common = VennSpan<IntegerT>(v1.start, v1.end);
            ex_v2.emplace_back(v2.start, v1.start);
        } else {
            common = VennSpan<IntegerT>(v1.start, v1.end);
            ex_v2.emplace_back(v2.start, v1.start);
            ex_v2.emplace_back(v1.end, v2.end);
        }
    } else if (v1.start == v2.start) {
        if (v2.end < v1.end) {
            common = VennSpan<IntegerT>(v1.start, v2.end);
            ex_v1.emplace_back(v2.end, v1.end);
        } else if (v2.end == v1.end) {
            common = VennSpan<IntegerT>(v1.start, v2.end);
        } else {
            common = VennSpan<IntegerT>(v1.start, v1.end);
            ex_v2.emplace_back(v1.end, v2.end);
        }
    } else if (v2.start < v1.end) {
        if (v2.end < v1.end) {
            common = VennSpan<IntegerT>(v2.start, v2.end);
            ex_v1.emplace_back(v1.start, v2.start);
            ex_v1.emplace_back(v2.end, v1.end);
        } else if (v2.end == v1.end) {
            common = VennSpan<IntegerT>(v2.start, v2.end);
            ex_v1.emplace_back(v1.start, v2.start);
        } else {
            common = VennSpan<IntegerT>(v2.start, v1.end);
            ex_v1.emplace_back(v1.start, v2.start);
            ex_v2.emplace_back(v1.end, v2.end);
        }
    } else {
        ex_v1.emplace_back(v1.start, v1.end);
        ex_v2.emplace_back(v2.start, v2.end);
    }
}

template <typename IntegerT>
void VennSpan<IntegerT>::combine(std::vector<VennSpan<IntegerT>> &spans) {

    if (1 >= spans.size()) {
        return;
    }

    std::priority_queue<aoc::VennSpan<IntegerT>, std::vector<aoc::VennSpan<IntegerT>>,
        std::greater<aoc::VennSpan<IntegerT>>>
        pq(spans.begin(), spans.end());

    std::vector<aoc::VennSpan<IntegerT>> replace{};

    while (pq.size() > 1) {
        auto sp1 = pq.top();
        pq.pop();
        auto sp2 = pq.top();
        if (sp2.start > sp1.end) {
            replace.push_back(sp1);
        } else if (sp1.end < sp2.end) {
            pq.pop();
            sp1.end = sp2.end;
            pq.push(sp1);
        } else {
            pq.pop();
            pq.push(sp1);
        }
    }
    replace.push_back(pq.top());
    spans = std::move(replace);
}

template <typename IntegerT>
void VennSpan<IntegerT>::clear() noexcept {
    start = 0;
    end = 0;
}

template class VennSpan<size_t>;
template class VennSpan<int32_t>;
template class VennSpan<uint32_t>;
} // namespace aoc
