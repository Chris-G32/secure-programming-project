#include <gtest/gtest.h>
#include "string_utils.hpp"

// Test for basic split case
TEST(StringUtilsTest, BasicSplit)
{
    std::string input = "Hello World";
    std::vector<std::string> expected = {"Hello", "World"};

    auto result = StringUtils::splitAtSpaces(input);

    EXPECT_EQ(result, expected);
}

// Test for an empty string
TEST(StringUtilsTest, EmptyString)
{
    std::string input = "";
    std::vector<std::string> expected = {};

    auto result = StringUtils::splitAtSpaces(input);

    EXPECT_EQ(result, expected);
}

// Test for a string with consecutive spaces
TEST(StringUtilsTest, ConsecutiveSpaces)
{
    std::string input = "Hello   World";
    std::vector<std::string> expected = {"Hello", "World"};

    auto result = StringUtils::splitAtSpaces(input);

    EXPECT_EQ(result, expected);
}

// Test for a string with no spaces
TEST(StringUtilsTest, NoSpaces)
{
    std::string input = "HelloWorld";
    std::vector<std::string> expected = {"HelloWorld"};

    auto result = StringUtils::splitAtSpaces(input);

    EXPECT_EQ(result, expected);
}

// Test for a string with leading and trailing spaces
TEST(StringUtilsTest, LeadingTrailingSpaces)
{
    std::string input = "  Hello World  ";
    std::vector<std::string> expected = {"Hello", "World"};

    auto result = StringUtils::splitAtSpaces(input);

    EXPECT_EQ(result, expected);
}

// Test for a string with only spaces
TEST(StringUtilsTest, OnlySpaces)
{
    std::string input = "     ";
    std::vector<std::string> expected = {};

    auto result = StringUtils::splitAtSpaces(input);

    EXPECT_EQ(result, expected);
}

// Test with a non-string container, e.g., std::vector<char>
TEST(StringUtilsTest, NonStringContainer)
{
    std::vector<char> input = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
    std::vector<std::string> expected = {"Hello", "World"};

    auto result = StringUtils::splitAtSpaces(input);

    EXPECT_EQ(result, expected);
}
