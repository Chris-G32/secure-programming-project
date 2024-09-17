#ifndef ATTENDEE_HPP
#define ATTENDEE_HPP

#include <string>
#include "attendee_state.hpp"
#include "typedefs.hpp"
#include <stdexcept>
#include <regex>
#include <cassert>
#include "regex_utils.hpp"
#include "log_entry.hpp"
class Attendee
{
public:
    Attendee() {}
    Attendee(const LogEntry &entry) : isEmployee(entry.isEmployee()), name(entry.getName())
    {
    }
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