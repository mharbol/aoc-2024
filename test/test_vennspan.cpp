
#include "util/VennSpan.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

TEST(TestVennSpan, TestComparisons) {
    const aoc::VennSpan<size_t> a(1, 2);
    const aoc::VennSpan<size_t> b(1, 2);
    const aoc::VennSpan<size_t> c(1, 4);
    const aoc::VennSpan<size_t> d(3, 5);

    ASSERT_EQ(a, b);
    ASSERT_LE(a, b);
    ASSERT_GE(a, b);

    ASSERT_NE(a, c);
    ASSERT_GT(c, a);
    ASSERT_GE(c, a);
    ASSERT_LT(a, c);
    ASSERT_LE(a, c);

    ASSERT_NE(c, d);
    ASSERT_GT(d, c);
    ASSERT_GE(d, c);
    ASSERT_LT(c, d);
    ASSERT_LE(c, d);
}

TEST(TestVenn, TestContains) {
    const aoc::VennSpan<uint32_t> vs(2, 7);
    ASSERT_TRUE(vs.contains(2));
    ASSERT_TRUE(vs.contains(3));
    ASSERT_FALSE(vs.contains(7));
    ASSERT_FALSE(vs.contains(0));
    ASSERT_FALSE(vs.contains(10));
}

TEST(TestVennSpan, TestVenn) {
    const aoc::VennSpan<int32_t> base_span(3, 14);
    aoc::VennSpan<int32_t> common(0, 0);
    std::vector<aoc::VennSpan<int32_t>> ex0{};
    std::vector<aoc::VennSpan<int32_t>> ex1{};

    // Same span (1)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(3, 14), ex0, common, ex1);
    ASSERT_EQ(common, aoc::VennSpan<int32_t>(3, 14));
    ASSERT_TRUE(ex0.empty());
    ASSERT_TRUE(ex1.empty());

    // totally out to the left (2)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(0, 2), ex0, common, ex1);
    ASSERT_TRUE(common.empty());
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(3, 14)}, ex0);
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(0, 2)}, ex1);

    // barely out to the left (3)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(1, 3), ex0, common, ex1);
    ASSERT_TRUE(common.empty());
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(3, 14)}, ex0);
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(1, 3)}, ex1);

    // totally off to the right (4)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(15, 18), ex0, common, ex1);
    ASSERT_TRUE(common.empty());
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(3, 14)}, ex0);
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(15, 18)}, ex1);

    // barely touch left, off right (5)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(14, 17), ex0, common, ex1);
    ASSERT_TRUE(common.empty());
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(3, 14)}, ex0);
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(14, 17)}, ex1);

    // totally covered by v1 (6)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(5, 11), ex0, common, ex1);
    std::vector<aoc::VennSpan<int32_t>> expected{};
    expected.emplace_back(3, 5);
    expected.emplace_back(11, 14);
    ASSERT_EQ(aoc::VennSpan<int32_t>(5, 11), common);
    ASSERT_EQ(expected, ex0);
    ASSERT_TRUE(ex1.empty());
    expected.clear();

    // touching left and fully inside right (7)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(3, 10), ex0, common, ex1);
    ASSERT_EQ(aoc::VennSpan<int32_t>(3, 10), common);
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(10, 14)}, ex0);
    ASSERT_TRUE(ex1.empty());

    // totally covered by v1 and touches right (8)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(8, 14), ex0, common, ex1);
    ASSERT_EQ(aoc::VennSpan<int32_t>(8, 14), common);
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(3, 8)}, ex0);
    ASSERT_TRUE(ex1.empty());

    // out left and filly inside right (9)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(2, 7), ex0, common, ex1);
    ASSERT_EQ(aoc::VennSpan<int32_t>(3, 7), common);
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(7, 14)}, ex0);
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(2, 3)}, ex1);

    // totally covered by v0 and off right (10)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(11, 18), ex0, common, ex1);
    ASSERT_EQ(aoc::VennSpan<int32_t>(11, 14), common);
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(3, 11)}, ex0);
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(14, 18)}, ex1);

    // totally covers v0 (11)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(0, 19), ex0, common, ex1);
    expected.emplace_back(0, 3);
    expected.emplace_back(14, 19);
    ASSERT_EQ(aoc::VennSpan<int32_t>(3, 14), common);
    ASSERT_TRUE(ex0.empty());
    ASSERT_EQ(expected, ex1);
    expected.clear();

    // totally covers v1 and barely touches right (12)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(1, 14), ex0, common, ex1);
    ASSERT_EQ(aoc::VennSpan<int32_t>(3, 14), common);
    ASSERT_TRUE(ex0.empty());
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(1, 3)}, ex1);

    // totally covered by v1 and off right (13)
    aoc::VennSpan<int32_t>::venn(base_span, aoc::VennSpan<int32_t>(3, 16), ex0, common, ex1);
    ASSERT_EQ(aoc::VennSpan<int32_t>(3, 14), common);
    ASSERT_TRUE(ex0.empty());
    ASSERT_EQ(std::vector<aoc::VennSpan<int32_t>>{aoc::VennSpan<int32_t>(14, 16)}, ex1);
}

TEST(TestVennSpan, TestCombine) {
    // test simple combine
    std::vector<aoc::VennSpan<uint32_t>> actual{};
    std::vector<aoc::VennSpan<uint32_t>> expected{};

    actual.emplace_back(2, 14);
    actual.emplace_back(5, 18);
    expected.emplace_back(2, 18);
    aoc::VennSpan<uint32_t>::combine(actual);
    ASSERT_EQ(expected, actual);

    // test triple combine
    actual.clear();
    expected.clear();
    actual.emplace_back(1, 4);
    actual.emplace_back(4, 6);
    actual.emplace_back(5, 11);
    expected.emplace_back(1, 11);
    aoc::VennSpan<uint32_t>::combine(actual);
    ASSERT_EQ(expected, actual);

    // test combine unrelated
    actual.clear();
    expected.clear();
    actual.emplace_back(6, 13);
    actual.emplace_back(1, 4);
    expected.emplace_back(1, 4);
    expected.emplace_back(6, 13);
    aoc::VennSpan<uint32_t>::combine(actual);
    ASSERT_EQ(expected, actual);

    // test combine overlap
    actual.clear();
    expected.clear();
    actual.emplace_back(1, 4);
    actual.emplace_back(2, 3);
    expected.emplace_back(1, 4);
    aoc::VennSpan<uint32_t>::combine(actual);
    ASSERT_EQ(expected, actual);

    // test combine multi
    actual.clear();
    expected.clear();
    actual.emplace_back(1, 19);
    actual.emplace_back(2, 12);
    actual.emplace_back(4, 30);
    actual.emplace_back(4, 15);
    expected.emplace_back(1, 30);
    aoc::VennSpan<uint32_t>::combine(actual);
    ASSERT_EQ(expected, actual);
}
