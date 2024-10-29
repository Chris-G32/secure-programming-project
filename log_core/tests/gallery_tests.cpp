#include <gtest/gtest.h>
#include "gallery.hpp"
#include <functional>
#include <algorithm>

class GalleryTest : public ::testing::Test
{
protected:
    // Setup any common variables or objects here if needed
};

TEST_F(GalleryTest, DefaultConstructor)
{
    Gallery gallery;
    EXPECT_TRUE(gallery.getLastUpdate() == 0);
    EXPECT_TRUE(gallery.getGalleryState().size() == 0);
}
// These tests are very basic as this is a highly state dependent program. It is simply checking that
TEST_F(GalleryTest, EmptyListConstructor)
{
    std::list<LogEntry> entries1;
    Gallery emptyGallery(entries1);
    std::cout << "Testing empty list constructor...";
    EXPECT_TRUE(emptyGallery.getLastUpdate() == 0) << "Update time should be 0 when there is no entries provided";
    EXPECT_TRUE(emptyGallery.getGalleryState().size() == 0) << "There should be no entries in the gallery, found more than 0";
}

TEST_F(GalleryTest, LogEntryListConstructor)
{
    std::cout << "Testing list ctor\n";
    LogEntry entry(true, true, "name", 1);
    std::list<LogEntry> entries;
    std::cout << "Pre list\n";
    entries.push_back(entry);
    std::cout << "Post list\n";

    Gallery gallery(entries);

    auto expectedTime = entry.getTime();
    auto actualTime = gallery.getLastUpdate();
    EXPECT_TRUE(expectedTime == actualTime) << "ExpectedTime: " << expectedTime << "\nActualTime: " << actualTime;
    EXPECT_TRUE(gallery.getGalleryState().size() == 1);
}

TEST_F(GalleryTest, ValidateStateUpdateTests)
{
    Gallery gallery;
    LogEntry entry(true, true, "name", 1);
    gallery.validateStateUpdate(gallery.attendeeFromEntry(entry), gallery.galleryEventFromEntry(entry));
}
TEST_F(GalleryTest, UpdateStateTest)
{
    Gallery gallery;
    LogEntry entry(true, true, "name", 1);
    gallery.updateState(gallery.attendeeFromEntry(entry), gallery.galleryEventFromEntry(entry));
}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}