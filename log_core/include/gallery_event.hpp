#ifndef GALLERY_EVENT_HPP
#define GALLERY_EVENT_HPP
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
    GalleryEvent(const GalleryEvent &rhs) : _time(rhs._time), _isArrival(rhs._isArrival) { _roomID = rhs._roomID == nullptr ? nullptr : new RoomID(*rhs._roomID); }
    ~GalleryEvent() { delete _roomID; }
};
#endif