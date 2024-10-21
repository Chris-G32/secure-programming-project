#include <gtest/gtest.h>
#include "gallery_event.hpp"

class GalleryEventTest : public ::testing::Test
{
protected:
    // Setup any common variables or objects here if needed
    Timestamp sampleTime = 1;
    RoomID sampleRoomID = 1;
};

TEST_F(GalleryEventTest, DefaultConstructor)
{
    GalleryEvent event;
    EXPECT_FALSE(event.getRoomId().first);
}

TEST_F(GalleryEventTest, ConstructorWithTimeAndArrival)
{
    GalleryEvent event(sampleTime, true);

    EXPECT_TRUE(event.isGalleryEntry());
    EXPECT_FALSE(event.isGalleryExit());
    EXPECT_FALSE(event.isRoomEntry());
    EXPECT_FALSE(event.isRoomExit());
}

TEST_F(GalleryEventTest, ConstructorWithTimeArrivalAndRoom)
{
    GalleryEvent event(sampleTime, true, sampleRoomID);

    EXPECT_FALSE(event.isGalleryEntry());
    EXPECT_FALSE(event.isGalleryExit());
    EXPECT_TRUE(event.isRoomEntry());
    EXPECT_FALSE(event.isRoomExit());
}

TEST_F(GalleryEventTest, ConstructorWithTimeExitAndRoom)
{
    GalleryEvent event(sampleTime, false, sampleRoomID);

    EXPECT_FALSE(event.isGalleryEntry());
    EXPECT_FALSE(event.isGalleryExit());
    EXPECT_FALSE(event.isRoomEntry());
    EXPECT_TRUE(event.isRoomExit());
}

TEST_F(GalleryEventTest, CopyConstructor)
{
    GalleryEvent original(sampleTime, true, sampleRoomID);
    GalleryEvent copy = original;

    EXPECT_FALSE(copy.isGalleryEntry());
    EXPECT_FALSE(copy.isGalleryExit());
    EXPECT_TRUE(copy.isRoomEntry());
    EXPECT_FALSE(copy.isRoomExit());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}