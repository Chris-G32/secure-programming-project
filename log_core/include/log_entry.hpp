#ifndef LOG_ENTRY_HPP
#define LOG_ENTRY_HPP
#include "typedefs.hpp"
#include <string>

class LogEntry
{
private:
    Timestamp _time;
    char _isEmployee;
    std::string _name;
    char _isArrival;
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
    LogEntry(std::string entry){
        std::string time = entry.substr(entry.begin(), entry.find_first_of(" "));
        entry.erase(entry.begin(), entry.find_first_of(" "));
        std::string isEmployee = entry.substr(entry.begin(), entry.find_first_of(" "));
        entry.erase(entry.begin(), entry.find_first_of(" "));
        std::string name = entry.substr(entry.begin(), entry.find_first_of(" "))
        entry.erase(entry.begin(), entry.find_first_of(" "));
        std::string isArrival = entry.substr(entry.begin(), entry.find_first_of(" "));
        if(isArrival == "-R"){
            entry.erase(entry.begin(), entry.find_first_of(" "));
            std::string roomID = entry.substr(entry.begin(), entry.end()-1);
        }
        else{
            //deleting since entry should be empty at this point;
            delete entry;
        }
        _time = std::stoul(time); _name = name; 
        if(isEmployee == "-E") { LogEntry::isEmployee(); }
        else { LogEntry::isGuest(); }
        if(isArrival == "-A") { LogEntry::isArrival(); _roomID = std::atoi("1") }
        else if (isArrival == "-R") {_roomID = std::atoi(roomID)}
        else { LogEntry::isArrival(); _roomID = std::atoi("1") }
        // if(isArrival == "R"){
        //     entry.erase(entry.begin(), entry.find_first_of(" "));
        //     std::string roomID = entry.substr(entry.begin(), entry.end()-1);
        // }
        // else{
        //     //deleting since entry should be empty at this point;
        //     delete entry;
        // }
        // _time = std::stoul(time); _name = name; 
        // if(isEmployee == "E") { LogEntry::isEmployee(); }
        // else { LogEntry::isGuest(); }
        // if(isArrival == "A") { LogEntry::isArrival(); _roomID = std::atoi("1") }
        // else if (isArrival == "R") {_roomID = std::atoi(roomID)}
        // else { LogEntry::isArrival(); _roomID = std::atoi("1") }
    }

    ~LogEntry() { delete _roomID; }
};
#endif