#include <gtest/gtest.h>
#include "adder.h"

TEST(adder, add) {
    EXPECT_EQ(adder::add(5,3), 8);
}

TEST(adder, div) {
    EXPECT_EQ(adder::divide(10,2), 5);
}

TEST(adder, mult) {
    EXPECT_EQ(adder::multi(10,2), 20);
}