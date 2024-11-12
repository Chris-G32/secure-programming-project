#include <gtest/gtest.h>
#include "log_file/log_file_cryptography_provider.hpp"
typedef std::vector<unsigned char>::iterator vecIt;
class LogFileCryptographyTests : public testing::Test
{
protected:
    std::string plaintext = "";
    std::string mykey = "weakkey";
    void outputSideBySide(vecIt src1, vecIt end1, vecIt src2, vecIt end2)
    {
        const int MAX_ITS = 30;
        int count = 0;
        auto it1 = src1;
        auto it2 = src2;
        std::cout << "L | R\n";
        std::cout << "-----\n";
        while (it1 != end1 || it2 != end2)
        {

            if (it1 == end1)
            {
                std::cout << "--";
            }
            else
            {
                std::cout << *it1 << ' ';
                it1++;
            }
            std::cout << '|';
            if (it2 == end2)
            {
                std::cout << "--";
            }
            else
            {
                std::cout << *it2 << ' ';
                it2++;
            }
            std::cout << "\n";
            count++;
            if (count > MAX_ITS)
            {
                break;
            }
        }
    }
};
TEST_F(LogFileCryptographyTests, TestEncryptDecrypt)
{
    LogFileCryptographyProvider provider;

    std::vector<unsigned char> buffer(plaintext.begin(), plaintext.end());
    auto encryptedResult = provider.encrypt(buffer, mykey);
    EXPECT_FALSE(std::equal(encryptedResult.begin(), encryptedResult.end(), plaintext.begin()));

    auto decryptResult = provider.decrypt(encryptedResult, mykey);
    EXPECT_TRUE(std::equal(plaintext.begin(), plaintext.end(), decryptResult.begin()));
}
TEST_F(LogFileCryptographyTests, TestHMAC)
{
    LogFileCryptographyProvider provider;
    std::vector<unsigned char> buffer(plaintext.begin(), plaintext.end());
    auto encryptedResult = provider.encrypt(buffer, mykey);
    auto hmac = provider.generateHMAC(encryptedResult, mykey);
    EXPECT_TRUE(provider.isNotModified(encryptedResult, hmac, mykey));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}