#include <gtest/gtest.h>
#include <sodium.h>

TEST(GalleryTest, Initialization)
{
    ASSERT_EQ(sodium_init(), 0) << "Sodium initialization failed";
}

TEST(SodiumTest, RandomNumberGeneration)
{
    uint32_t random_number1, random_number2;
    randombytes_buf(&random_number1, sizeof(random_number1));
    randombytes_buf(&random_number2, sizeof(random_number2));

    // This test has a very small chance of failing if the same number is generated twice
    EXPECT_NE(random_number1, random_number2) << "Generated numbers should be different";
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}