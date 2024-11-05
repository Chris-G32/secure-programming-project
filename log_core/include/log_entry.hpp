#ifndef LOG_ENTRY_HPP
#define LOG_ENTRY_HPP
#include "typedefs.hpp"
#include <string>
#include "regex_utils.hpp"
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
    void LogEntry::setTimeFromString(const std::string &timeStr)
    {
        const Timestamp MAX_TIMESTAMP = 1073741823U;
        if (!isNumeric(timeStr) || timeStr.length() > 10)
        {
            // TODO: Custom error for failure to set a logentry value
            throw std::runtime_error("Invalid Timestamp String");
        }
        char **end;
        unsigned long timestamp = std::strtoul(timeStr.c_str(), end, 10);
        if (timestamp > MAX_TIMESTAMP || timestamp < 1)
        {
            throw std::overflow_error("Timestamp is outside of acceptable range.");
        }
        _time = timestamp;
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
    friend class LogEntryParser;
    
    // static LogEntry tryParseFromCommandLineFormat(const std::string &line)
    // {
    //     bool isArrival, isEmployee;
    //     std::string name;
    //     Timestamp time;
    //     RoomID roomID;
    //     // Parse the line and return a LogEntry
    //     return LogEntry();
    // }
    Timestamp getTime() const { return _time; }
    const std::string &getName() const { return _name; }
    friend class LogEntryFactory;
    friend class LogEntryParser;
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
        if (!isAlphabetical(name))
        {
            throw std::invalid_argument("Name must be alphabetical and not empty string.");
        }
        if (!(time > 0))
        {
            throw std::invalid_argument("Time must be greater than 0.");
        }
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