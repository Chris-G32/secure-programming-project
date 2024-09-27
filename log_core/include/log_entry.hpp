#ifndef LOG_ENTRY_HPP
#define LOG_ENTRY_HPP
#include "typedefs.hpp"
#include <string>
#include <vector>
#include <set>
#include <list>
#include <map>

class LogEntry
{
private:
    Timestamp _time;
    bool _isEmployee;
    std::string _name;
    bool _isArrival;
    RoomID *_roomID = nullptr;

public:
    bool isEmployee() { return _isEmployee; }
    bool isGuest() { return !_isEmployee; }
    bool isArrival() { return _isArrival; }
    bool isLeave() { return !_isArrival; }
    std::pair<bool, RoomID> getRoomID()
    {
        if (_roomID == nullptr)
        {
            return std::make_pair(false, 0);
        }
        return std::make_pair(true, *_roomID);
    }
    std::string logRead(std::string);
    ~LogEntry() { delete _roomID; }
};

#endif