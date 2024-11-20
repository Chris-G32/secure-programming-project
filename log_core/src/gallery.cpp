#include "gallery.hpp"
#include <stdexcept>
#include <algorithm>
#include <list>
bool Gallery::validateStateUpdate(const Attendee &attendee, const GalleryEvent &event) const
{
    if (event._time <= _lastUpdateTime)
    {
        return false;
    }

    auto entry = _galleryState.find(attendee);

    if (entry != _galleryState.end())
    {
        const AttendeeState &state = entry->second.second;
        GalleryEvent mostRecentEventForAttendee = entry->second.first.back();
        switch (state)
        {
        case OutsideGallery:
            return event.isGalleryEntry();
        case InGallery:
            // You may only enter the gallery or a room from the in gallery state
            return event.isGalleryExit() || event.isRoomEntry();
        case InRoom:
            if (event.isRoomExit())
            {
                return *(event._roomID) == *(entry->second.first.back()._roomID);
            }
            return false;
        default:
            // This should never be hit really
            throw std::runtime_error("Log is in invalid state");
        };
    }
    return event.isGalleryEntry();
}
/// @brief Gets the state achieved by an event, does no validation on event
/// @param event The event
/// @return The state specified by the event
AttendeeState Gallery::getNewState(const GalleryEvent &event)
{
    if (event.isGalleryEntry() || event.isRoomExit())
    {
        return InGallery;
    }
    if (event.isRoomEntry())
    {
        return InRoom;
    }
    if (event.isGalleryExit())
    {
        return OutsideGallery;
    }
    throw std::logic_error("Failed to account for a case when calculating the new state an event achieves.");
}

void Gallery::updateState(const Attendee &attendee, const GalleryEvent &event)
{
    if (!validateStateUpdate(attendee, event))
    {
        throw std::runtime_error("Log is in invalid state");
    }
    auto entry = _galleryState.find(attendee);
    if (entry == _galleryState.end())
    {
        EventListStatePair stateInfo;
        stateInfo.first.push_back(event);
        stateInfo.second = getNewState(event);
        _galleryState.insert(std::make_pair(attendee, stateInfo));
    }
    else
    {
        // Update log of events
        entry->second.first.push_back(event);
        // Update stored state
        entry->second.second = getNewState(event);
    }

    _lastUpdateTime = event._time;
}
void Gallery::updateState(const LogEntry &entry)
{
    updateState(attendeeFromEntry(entry), galleryEventFromEntry(entry));
}
void Gallery::printState() {}

Gallery::Gallery(const std::list<LogEntry> &entries)
{
    _lastUpdateTime = 0;
    for (const auto &entry : entries)
    {
        updateState(entry);
    }
}