#ifndef GALLERY_HPP
#define GALLERY_HPP
#include <map>
#include <list>
#include "attendee.hpp"
#include "gallery_event.hpp"
#include "log_entry.hpp"
#include "attendee_state.hpp"
typedef std::pair<std::list<GalleryEvent>, AttendeeState> EventListStatePair;
class Gallery
{
private:
    Timestamp _lastUpdateTime = 0;
    std::map<Attendee, EventListStatePair> _galleryState;
    bool validateStateUpdate(const Attendee &, const GalleryEvent &);
    AttendeeState getNewState(const GalleryEvent &);

public:
    Gallery(const std::list<LogEntry> &entries);
    ~Gallery() {}

    void updateState(const Attendee &, const GalleryEvent &);
};

#endif