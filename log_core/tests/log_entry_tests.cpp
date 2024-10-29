#include <gtest/gtest.h>
#include "log_entry.hpp"
#include <random>

struct ExpectedEntryValues
{
    bool arrival;
    bool employee;
    std::string name;
    Timestamp time;
};

class LogEntryTests : public testing::Test
{
protected:
    std::string gen_random_str(const int len)
    {
        static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        std::string tmp_s;
        tmp_s.reserve(len);

        for (int i = 0; i < len; ++i)
        {
            tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
        }

        return tmp_s;
    }
    ExpectedEntryValues createRandom()
    {
        ExpectedEntryValues expected;
        expected.arrival = std::rand() % 2 == 1 ? true : false;
        expected.employee = std::rand() % 2 == 1 ? true : false;
        expected.name = gen_random_str((std::rand() % 40) + 1);
        expected.time = std::rand() % (RAND_MAX - 1) + 1;
        return expected;
    }
};

TEST_F(LogEntryTests, DefaultConstructor)
{
    std::cout << "Verifying roomID is null in default constructor";
    LogEntry entry;
    auto roomIDPair = entry.getRoomID();
    EXPECT_FALSE(roomIDPair.first);
    EXPECT_EQ(roomIDPair.second, 0);
}
TEST_F(LogEntryTests, NoRoomIdConstructor)
{
    auto expectedData = createRandom();
    std::cout << "Testing constructor with no roomID\n";
    LogEntry entry(expectedData.arrival, expectedData.employee, expectedData.name, expectedData.time);

    EXPECT_EQ(entry.isArrival(), expectedData.arrival);
    EXPECT_EQ(entry.isEmployee(), expectedData.employee);
    EXPECT_EQ(entry.getName(), expectedData.name);
    EXPECT_EQ(entry.getTime(), expectedData.time);
    EXPECT_EQ(entry.getRoomID().first, false);
}
TEST_F(LogEntryTests, WithRoomIdConstructor)
{
    auto expectedData = createRandom();
    std::cout << "Testing constructor with roomID\n";
    auto expectedRoomID = (std::rand() % RAND_MAX - 1) + 1;
    LogEntry entry(expectedData.arrival, expectedData.employee, expectedData.name, expectedData.time, expectedRoomID);
    // std::cout << std::endl
    //           << entry.summary() << std::endl;
    EXPECT_EQ(entry.isArrival(), expectedData.arrival) << "Arrival does not match";
    EXPECT_EQ(entry.isEmployee(), expectedData.employee);
    EXPECT_EQ(entry.getName(), expectedData.name);
    EXPECT_EQ(entry.getTime(), expectedData.time);
    EXPECT_EQ(entry.getRoomID().first, true);
    EXPECT_EQ(entry.getRoomID().second, expectedRoomID) << "Got to room";
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}