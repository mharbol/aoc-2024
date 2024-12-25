
#include "solution/Day17.h"
#include <gtest/gtest.h>

TEST(TestElfComputer, TestCombo) {
    aoc::ElfComputer computer(1, 2, 3, {});
    ASSERT_EQ(0, computer.combo(0));
    ASSERT_EQ(1, computer.combo(1));
    ASSERT_EQ(2, computer.combo(2));
    ASSERT_EQ(3, computer.combo(3));
    ASSERT_EQ(1, computer.combo(4));
    ASSERT_EQ(2, computer.combo(5));
    ASSERT_EQ(3, computer.combo(6));
}

TEST(TestElfComputer, TestAdv) {
    aoc::ElfComputer computer(729, 0, 0, {0, 1, 5, 4, 3, 0});
    computer.adv(1);
    ASSERT_EQ(364, computer.reg_A);
    ASSERT_EQ(0, computer.reg_B);
    ASSERT_EQ(0, computer.reg_C);
    ASSERT_EQ(2, computer.ip);

    computer.ip = 0;
    computer.adv(3);
    ASSERT_EQ(45, computer.reg_A);
    ASSERT_EQ(0, computer.reg_B);
    ASSERT_EQ(0, computer.reg_C);
    ASSERT_EQ(2, computer.ip);
}

TEST(TestElfComputer, TestBdv) {
    aoc::ElfComputer computer(729, 0, 0, {0, 1, 5, 4, 3, 0});
    computer.bdv(1);
    ASSERT_EQ(729, computer.reg_A);
    ASSERT_EQ(364, computer.reg_B);
    ASSERT_EQ(0, computer.reg_C);
    ASSERT_EQ(2, computer.ip);

    computer.ip = 0;
    computer.bdv(3);
    ASSERT_EQ(729, computer.reg_A);
    ASSERT_EQ(91, computer.reg_B);
    ASSERT_EQ(0, computer.reg_C);
    ASSERT_EQ(2, computer.ip);
}

TEST(TestElfComputer, TestCdv) {
    aoc::ElfComputer computer(729, 4, 0, {0, 4, 5, 4, 3, 0});
    computer.cdv(1);
    ASSERT_EQ(729, computer.reg_A);
    ASSERT_EQ(4, computer.reg_B);
    ASSERT_EQ(364, computer.reg_C);
    ASSERT_EQ(2, computer.ip);

    computer.ip = 0;
    computer.cdv(5);
    ASSERT_EQ(729, computer.reg_A);
    ASSERT_EQ(4, computer.reg_B);
    ASSERT_EQ(45, computer.reg_C);
    ASSERT_EQ(2, computer.ip);
}

TEST(TestElfComputer, TestBxl) {
    aoc::ElfComputer computer(729, 4, 0, {0, 4, 5, 4, 3, 0});
    computer.bxl(6);
    ASSERT_EQ(729, computer.reg_A);
    ASSERT_EQ(2, computer.reg_B);
    ASSERT_EQ(0, computer.reg_C);
    ASSERT_EQ(2, computer.ip);
}

TEST(TestElfComputer, TestBst) {
    aoc::ElfComputer computer(729, 4, 0, {0, 4, 5, 4, 3, 0});
    computer.bst(3);
    ASSERT_EQ(729, computer.reg_A);
    ASSERT_EQ(3, computer.reg_B);
    ASSERT_EQ(0, computer.reg_C);
    ASSERT_EQ(2, computer.ip);

    computer.bst(4);
    ASSERT_EQ(729, computer.reg_A);
    ASSERT_EQ(729 % 8, computer.reg_B);
    ASSERT_EQ(0, computer.reg_C);
    ASSERT_EQ(4, computer.ip);
}

TEST(TestElfComputer, TestBxc) {
    aoc::ElfComputer computer(729, 4, 12, {0, 4, 5, 4, 3, 0});
    computer.bxc(3);
    ASSERT_EQ(729, computer.reg_A);
    ASSERT_EQ(8, computer.reg_B);
    ASSERT_EQ(12, computer.reg_C);
    ASSERT_EQ(2, computer.ip);
}

TEST(TestElfComputer, TestJnz) {
    aoc::ElfComputer computer(729, 4, 12, {0, 4, 5, 4, 3, 0});
    computer.jnz(3);
    ASSERT_EQ(729, computer.reg_A);
    ASSERT_EQ(4, computer.reg_B);
    ASSERT_EQ(12, computer.reg_C);
    ASSERT_EQ(3, computer.ip);

    computer.reg_A = 0;
    computer.jnz(3);
    ASSERT_EQ(0, computer.reg_A);
    ASSERT_EQ(4, computer.reg_B);
    ASSERT_EQ(12, computer.reg_C);
    ASSERT_EQ(5, computer.ip);
}

TEST(TestElfComputer, TestExamples) {
    aoc::ElfComputer c1(0, 0, 9, {2, 6});
    c1.runProgram();
    ASSERT_EQ(1, c1.reg_B);

    aoc::ElfComputer c2(10, 0, 0, {5, 0, 5, 1, 5, 4});
    c2.runProgram();
    ASSERT_EQ("0,1,2", c2.getOutput());

    aoc::ElfComputer c3(2024, 0, 0, {0, 1, 5, 4, 3, 0});
    c3.runProgram();
    ASSERT_EQ("4,2,5,6,7,7,7,7,3,1,0", c3.getOutput());
    ASSERT_EQ(0, c3.reg_A);

    aoc::ElfComputer c4(0, 29, 0, {1, 7});
    c4.runProgram();
    ASSERT_EQ(26, c4.reg_B);

    aoc::ElfComputer c5(0, 2024, 43690, {4, 0});
    c5.runProgram();
    ASSERT_EQ(44354, c5.reg_B);
}
