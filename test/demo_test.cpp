#include <gtest/gtest.h>
#include "adder.h"

TEST(adder, add) {
    EXPECT_EQ(adder::add(5,3), 8);
}