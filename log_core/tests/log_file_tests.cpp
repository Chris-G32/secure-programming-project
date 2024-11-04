#include <gtest/gtest.h>
#include "log_entry.hpp"
#include <random>

class LogFileTests : public testing::Test
{
protected:
    
};

TEST_F(LogFileTests, DefaultConstructor)
{
    
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}