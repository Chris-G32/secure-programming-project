#include <gtest/gtest.h>
#include "log_entry_factory.hpp"
#include "gallery.hpp"

class GalleryTest : public ::testing::Test, protected LogEntry
{
protected:
    LogEntryFactory entryFactory;
    // Setup any common variables or objects here if needed
};

TEST_F(GalleryTest, DefaultConstructor)
{
    Gallery gallery;
    EXPECT_TRUE(gallery.getLastUpdate() == 0);
    EXPECT_TRUE(gallery.getGalleryState().size() == 0);
}
TEST_F(GalleryTest, LogEntryListConstructor)
{
    std::list<LogEntry> entries1;
    Gallery emptyGallery(entries1);
    EXPECT_TRUE(emptyGallery.getLastUpdate() == 0);
    EXPECT_TRUE(emptyGallery.getGalleryState().size() == 0);
    std::list<LogEntry> entries2 = {};
    Gallery gallery(entries2);
    EXPECT_TRUE(emptyGallery.getLastUpdate() == 0);
    EXPECT_TRUE(emptyGallery.getGalleryState().size() == 0);
}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}