#ifndef __AOC_VENN_SPAN_H__
#define __AOC_VENN_SPAN_H__

#include <type_traits>
#include <vector>
namespace aoc {

/**
 * Another little bit of code before this year's event starts.
 * I know C++20 has `std::span` and other cool things like that, I just wanted to make this the
 * way that makes sense to me. Not sure if or when I'll need it for 2024 but it would be nice
 * to have if I need something like this or at the very least it's a fun thing to make.
 *
 * Represents a span of integers which can be "venned" to get common/exclusive ranges and other
 * cool things like that.
 */
template <typename IntegerT>
class VennSpan {
    static_assert(std::is_integral<IntegerT>::value, "Type must be integral");

private:
    IntegerT start{}, end{};

public:
    VennSpan(IntegerT start, IntegerT end) : start(start), end(end) {}
    ~VennSpan() = default;

    static void venn(const VennSpan<IntegerT> &v1, const VennSpan<IntegerT> &v2,
        std::vector<VennSpan<IntegerT>> &ex_v1, VennSpan<IntegerT> &common,
        std::vector<VennSpan<IntegerT>> &ex_v2);

    static void combine(std::vector<VennSpan<IntegerT>> &spans);

    void clear() noexcept;

    inline bool empty() const {
        return start == end;
    }

    inline bool contains(IntegerT n) const {
        return start <= n && end > n;
    }

    inline IntegerT getStart() const {
        return start;
    }

    inline IntegerT getEnd() const {
        return end;
    }

    inline bool operator==(const VennSpan<IntegerT> &rhs) const {
        return start == rhs.start && end == rhs.end;
    }

    inline bool operator!=(const VennSpan<IntegerT> &rhs) const {
        return start != rhs.start || end != rhs.end;
    }

    inline bool operator<(const VennSpan<IntegerT> &rhs) const {
        return start < rhs.start ? true : end < rhs.end;
    }

    inline bool operator>(const VennSpan<IntegerT> &rhs) const {
        return start > rhs.start ? true : end > rhs.end;
    }

    inline bool operator<=(const VennSpan<IntegerT> &rhs) const {
        return !(*this > rhs);
    }

    inline bool operator>=(const VennSpan<IntegerT> &rhs) const {
        return !(*this < rhs);
    }
};
} // namespace aoc
//
#endif
