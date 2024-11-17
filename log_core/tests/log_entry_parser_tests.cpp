#include <gtest/gtest.h>
#include "log_file/log_file.hpp"
#include <random>

class LogFileTests : public testing::Test
{
protected:
    LogEntryParser &parser = LogFileEntryParser::instance();
    LogFileCryptographyProvider cryptoProvider;
};

TEST_F(LogFileTests, DefaultConstructor)
{
    LogFile logFile(parser,cryptoProvider);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}