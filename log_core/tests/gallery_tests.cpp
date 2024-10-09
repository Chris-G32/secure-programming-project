#include "gallery.hpp"
#include <cassert>
#include <sodium.h>
class GalleryTests : public Gallery
{
public:
    GalleryTests() : Gallery() {}
    void validateStateUpdateTests()
    {
        Attendee attendee("test", false);
        GalleryEvent event(10, true);
        
        assert(validateStateUpdate(attendee, event));
        GalleryEvent event2(10, false);
        assert(!validateStateUpdate(attendee, event2));
    }
};
int main()
{
    GalleryTests tests;
    tests.validateStateUpdateTests();
}