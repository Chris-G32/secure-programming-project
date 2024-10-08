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
    RoomID *_roomID = nullptr;

public:
    void isEmployee() { _isEmployee = true; }
    void isGuest() { _isEmployee = false; }
    void isArrival() { _isArrival = true; }
    void isLeave() { _isArrival = false; }
    std::pair<bool, RoomID> getRoomID()
    {
        if (_roomID == nullptr)
        {
            return std::make_pair(false, 0);
        }
        return std::make_pair(true, *_roomID);
    }
    LogEntry(std::string time, std::string name, std::string isEmployee, std::string isArrival){
        if(isEmployee == "-E") { LogEntry::isEmployee(); }
        else { LogEntry::isGuest(); }
        if(isArrival == "-A") { LogEntry::isArrival(); _roomID =  }
        else if (isArrival == "-R");
        _time = std::stoul(time); _name = name; 
    }

    ~LogEntry() { delete _roomID; }
};
#endif