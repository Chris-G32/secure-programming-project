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

protected:
    AttendeeState getNewState(const GalleryEvent &);
    void insertLogEntry(const LogEntry &entry);

public:
    bool validateStateUpdate(const Attendee &, const GalleryEvent &);
    Attendee attendeeFromEntry(const LogEntry &entry) const { return Attendee(entry.getName(), entry.isEmployee()); }
    GalleryEvent galleryEventFromEntry(const LogEntry &entry) const
    {
        auto roomIDPair = entry.getRoomID();
        return roomIDPair.first ? GalleryEvent(entry.getTime(), entry.isArrival(), roomIDPair.second) : GalleryEvent(entry.getTime(), entry.isArrival());
    }
    Timestamp getLastUpdate() { return _lastUpdateTime; }
    const std::map<Attendee, EventListStatePair> &getGalleryState() { return _galleryState; }
    Gallery(const std::list<LogEntry> &entries);
    Gallery() {}
    ~Gallery() {}
    void printState();
    void updateState(const LogEntry &);
    void updateState(const Attendee &, const GalleryEvent &);
};

#endif