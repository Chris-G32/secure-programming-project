#include <gtest/gtest.h>
#include "log_file_writer.hpp"
#include "log_file_reader.hpp"
#include <iostream>
#include <streambuf>
class LogFileWriterTests : public testing::Test
{
protected:
    LogEntryParser &parser = LogFileEntryParser::instance();
    LogFileCryptographyProvider cryptoProvider;
};

TEST_F(LogFileWriterTests, TestEmptyWrite)
{
    Gallery emptyGallery;
    std::string key = "abced";
    LogFileWriter writer(cryptoProvider);
    std::stringstream stream;
    ASSERT_THROW(writer.write(emptyGallery, stream, key), std::runtime_error);
}
TEST_F(LogFileWriterTests, TestOneEntryWrite)
{
    LogEntry entry(true, true, "name", 1);
    std::list<LogEntry> entries;
    std::cout << "Pre list\n";
    entries.push_back(entry);
    std::cout << "Post list\n";

    Gallery gallery(entries);
    std::string key = "abced";
    LogFileWriter writer(cryptoProvider);
    std::stringstream stream;
    writer.write(gallery, stream, key);
    std::cout << "Write Complete...\n";
    stream.seekg(0);
    LogFileReader reader(parser, cryptoProvider);
    auto result = reader.load(stream, key);
    auto storedGallery = result.authorizedGalleryGet(key);
    ASSERT_EQ(storedGallery.getLastUpdate(), gallery.getLastUpdate());
    ASSERT_EQ(storedGallery.getGalleryState().size(), gallery.getGalleryState().size());
    ASSERT_EQ(storedGallery.getGalleryState().begin()->first.getName(), entry.getName());
}

int main(int argc, char **argv)
{
    /*LogEntry entry(true, true, "name", 1);
    std::list<LogEntry> entries;
    std::cout << "Pre list\n";
    entries.push_back(entry);
    std::cout << "Post list\n";

    Gallery gallery(entries);*/
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}