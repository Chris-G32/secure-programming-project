#ifndef GALLERY_EVENT_HPP
#define GALLERY_EVENT_HPP
#include "typedefs.hpp"
class GalleryEvent
{
private:
    Timestamp _time;
    bool _isArrival;
    RoomID *_roomID = nullptr;
    friend class Gallery;

public:
    bool isGalleryEntry() const { return _isArrival && _roomID == nullptr; }
    bool isGalleryExit() const { return !_isArrival && _roomID == nullptr; }
    bool isRoomEntry() const { return _isArrival && _roomID != nullptr; }
    bool isRoomExit() const { return !_isArrival && _roomID != nullptr; }
    GalleryEvent() {}
    GalleryEvent(Timestamp time, bool arrival)
    {
        _time = time;
        _isArrival = arrival;
    }
    GalleryEvent(Timestamp time, bool arrival, RoomID room) : GalleryEvent(time, arrival)
    {
        _roomID = new RoomID(room);
    }
    GalleryEvent(const GalleryEvent &rhs) : _time(rhs._time), _isArrival(rhs._isArrival) { _roomID = rhs._roomID == nullptr ? nullptr : new RoomID(*rhs._roomID); }
    ~GalleryEvent() { delete _roomID; }
};
#endif