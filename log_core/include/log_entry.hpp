#ifndef LOG_ENTRY_HPP
#define LOG_ENTRY_HPP
#include "typedefs.hpp"
#include <string>
#include <sstream>

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
    void setTime(const Timestamp &time)
    {
        _time = time;
    }
    void setIsEmployee(bool isEmployee)
    {
        _isEmployee = isEmployee;
    }
    void setName(const std::string &name)
    {
        _name = name;
    }
    void setIsArrival(bool isArrival)
    {
        _isArrival = isArrival;
    }
    void setRoomID(RoomID roomID)
    {
        if (_roomID != nullptr)
        {
            delete _roomID;
        }
        _roomID = new RoomID(roomID);
    }

    std::string toFileFormat() const
    {
        std::ostringstream oss;
        char employeeStatus = _isEmployee ? 'E' : 'G';
        char arrivalStatus = _isArrival ? 'A' : 'L';
        const char SPACE = ' ';
        oss << _time << SPACE << employeeStatus << SPACE << _name << SPACE << arrivalStatus;
        if (_roomID != nullptr)
        {
            oss << SPACE << *_roomID;
        }
        return oss.str();
    }
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
    friend class LogEntryFactory;

    Timestamp getTime() const { return _time; }
    const std::string &getName() const { return _name; }
    std::pair<bool, RoomID> getRoomID() const
    {
        if (_roomID == nullptr)
        {
            return std::make_pair(false, 0);
        }
        return std::make_pair(true, *_roomID);
    }
    LogEntry() : _roomID(nullptr) {}
    LogEntry(bool isArrival, bool isEmployee, std::string name, Timestamp time) : _roomID(nullptr)
    {
        _isArrival = isArrival;
        _isEmployee = isEmployee;
        _name = name;
        _time = time;
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