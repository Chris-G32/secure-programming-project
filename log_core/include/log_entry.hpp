#ifndef LOG_ENTRY_HPP
#define LOG_ENTRY_HPP
#include "typedefs.hpp"
#include <string>
class LogEntry
{
private:
    Timestamp _time;
    bool _isEmployee;
    std::string _name;
    bool _isArrival;
    RoomID *_roomID;
    void copyFrom(const LogEntry &rhs)
    {
        _time = rhs._time;
        _isEmployee = rhs._isEmployee;
        _name = rhs._name;
        _isArrival = rhs._isArrival;

        // Deep copy the RoomID if it exists
        if (rhs.getRoomID().first)
        {
            _roomID = new RoomID(*rhs._roomID);
        }
        else
        {
            _roomID = nullptr;
        }
    }

public:
    // std::string summary() const
    // {
    //     std::string summaryText;
    //     summaryText += _isEmployee ? "Employee " : "Guest ";
    //     summaryText += _name + " ";
    //     summaryText += _isArrival ? "arrived" : "left";
    //     summaryText += " at " + std::to_string((unsigned int)_time); // Assuming Timestamp can be converted to string

    //     auto roomIDPair = getRoomID();
    //     if (roomIDPair.first)
    //     {
    //         summaryText += " in room " + std::to_string((unsigned int)roomIDPair.second);
    //     }

    //     return summaryText;
    // }
    void operator=(const LogEntry &rhs)
    {
        copyFrom(rhs);
    }
    bool isEmployee() const { return _isEmployee; }
    bool isGuest() const { return !_isEmployee; }
    bool isArrival() const { return _isArrival; }
    bool isLeave() const { return !_isArrival; }
    Timestamp getTime() const { return _time; }
    const std::string &getName() const { return _name; }
    friend class LogEntryFactory;
    std::pair<bool, RoomID> getRoomID() const
    {
        if (_roomID == nullptr)
        {
            return std::make_pair(false, 0);
        }
        return std::make_pair(true, *_roomID);
    }
    LogEntry() : _roomID(nullptr) {}
    LogEntry(bool isArrival, bool isEmployee, std::string name, Timestamp time) : _isArrival(isArrival), _isEmployee(isEmployee), _name(name), _time(time), _roomID(nullptr)
    {
    }
    LogEntry(bool isArrival, bool isEmployee, std::string name, Timestamp time, RoomID roomID) : LogEntry(isArrival, isEmployee, name, time) { _roomID = new unsigned int(roomID); }

    LogEntry(const LogEntry &rhs)
        : _roomID(nullptr) // Initialize _roomID to nullptr before calling copyFrom
    {
        copyFrom(rhs);
    }

    ~LogEntry()
    {
        if (_roomID != nullptr)
        {
            delete _roomID;
        };
    }
};
#endif