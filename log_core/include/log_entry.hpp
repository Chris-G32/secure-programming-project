#ifndef LOG_ENTRY_HPP
#define LOG_ENTRY_HPP
#include <string>
#include <regex>
#include "typedefs.hpp"
#include "actions.hpp"
using std::string;
/// @brief Represents a log entry stored in a log file. Provides methods to convert into our internal representation.
class LogEntry
{
private:
    Timestamp _time;
    std::string _name;
    bool _isEmployee;
    bool _isArrival;
    RoomID *_roomID = nullptr;
    LogEntry() {}

public:
    friend class LogEntryFactory;
    /// @brief Gets the room ID
    /// @return A pair with the first entry indicating whether or not there was a RoomID provided to this log. The second entry is the id.
    std::pair<bool, RoomID> getRoomID() const
    {
        if (_roomID == nullptr)
        {
            return std::make_pair(false, 0);
        }
        return std::make_pair(true, *_roomID);
    }
    Timestamp getTimestamp() const { return _time; }
    std::string getName() const { return _name; }
    bool isEmployee() const { return _isEmployee; }
    bool isGuest() const { return !_isEmployee; }
    bool isArrival() const { return _isArrival; }
    bool isLeave() const { return !_isArrival; }
    bool isArrivalToGallery() const { return isArrival() && _roomID == nullptr; }
    Action getAction() { return Action(isArrival() ? Arrive : Leave); }
    ~LogEntry()
    {
        if (_roomID != nullptr)
            delete _roomID;
    }
};

#endif