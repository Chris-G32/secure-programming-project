#ifndef ATTENDEE_HPP
#define ATTENDEE_HPP

#include <string>
#include "attendee_state.hpp"
#include "typedefs.hpp"
#include <stdexcept>
#include <regex>

class Attendee
{
public:
    Attendee() {}
    Attendee(const Attendee &attendee) : isEmployee(attendee.isEmployee), name(attendee.name)
    {
    }
    bool isEmployee;
    std::string name;
    bool operator<(const Attendee &rhs) const
    {
        if (rhs.isEmployee == isEmployee)
        {
            return name < rhs.name;
        }
        // If they are not both employees, guests will be considered less than employees
        return !isEmployee;
    }
};
class LogEntry
{
private:
    LogEntry() {}

public:
    // Takes entries in the form of -k key -T time etc...
    static LogEntry loadFromArgs(int argc, char **argv)
    {
        LogEntry entry;
        if (argc != 8 | argc != 10)
        {
            throw std::length_error("Invalid argument length for logentry");
        }
        if (argc == 10)
        {
            if (argv[7] != "-R")
            {
                throw std::runtime_error("Expected -R flag.");
            }
            std::string roomNumArg = argv[8];
            std::regex isNumeric(R"([0-9]+)");
            if (!std::regex_match(roomNumArg, isNumeric))
            {
                throw std::runtime_error("Invalid room id.");
            }
            char **end;
            const unsigned int MAX_ROOM_ID = 1073741823U;
            unsigned long roomId = std::strtoul(roomNumArg.c_str(), end, 10);
            if (roomId > MAX_ROOM_ID)
            {
                throw std::overflow_error("Invalid room id.");
            }
            entry.room = new RoomID(roomId);
        }

        std::regex logFileNameValid(R"(\s[a-zA-z0-9._]+)");
        std::string logFileName = argv[argc - 1];
        std::regex_match(logFileName, logFileNameValid);
    }

    ~LogEntry()
    {
        if (room != nullptr)
            delete room;
    }
    Timestamp time;
    std::string name;
    bool isEmployee;
    char action;
    RoomID *room = nullptr;
    std::string logFile;
};
class EventLog
{
private:
    AttendeeState *_state;
    Timestamp _timestamp;

public:
    bool operator==(EventLog &other) const
    {
        return _timestamp == other._timestamp && _state->getState() == other._state->getState();
    }
    Timestamp getTimestamp() const { return _timestamp; }
    AttendeeState *getState() const
    {
        return _state;
    }
    void transitionState(AttendeeState *newState)
    {
        delete _state;
        _state = newState;
    }
    EventLog(Timestamp time);
    EventLog(const EventLog &);
    ~EventLog();
};

EventLog::EventLog(Timestamp time) : _state(new OutsideState()), _timestamp(time)
{
}
EventLog::EventLog(const EventLog &toCopy)
{
    _timestamp = toCopy._timestamp;
    _state = toCopy._state->clone();
}
EventLog::~EventLog()
{
    delete _state;
}

#endif