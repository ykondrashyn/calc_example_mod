#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "../calculate_module.h"
}

TEST(CalculateTest, Addition) {
    EXPECT_EQ(calculate(5, 3, (char *)"add"), 8);
    EXPECT_EQ(calculate(-5, 3, (char *)"add"), -2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
