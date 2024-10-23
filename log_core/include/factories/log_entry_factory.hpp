#ifndef LOG_ENTRY_FACTORY_HPP
#define LOG_ENTRY_FACTORY_HPP
#include "../log_entry.hpp"
class LogEntryBuilder
{
public:
};

class LogEntryFactory
{
private:
    /* data */
public:
    LogEntry create(bool isArrival, bool isEmployee, std::string name, Timestamp time);
    LogEntry create(bool isArrival, bool isEmployee, std::string name, Timestamp time, RoomID roomID);
    LogEntryFactory(/* args */);
    ~LogEntryFactory();
};

LogEntryFactory::LogEntryFactory(/* args */)
{
}

LogEntryFactory::~LogEntryFactory()
{
}
LogEntry LogEntryFactory::create(bool isArrival, bool isEmployee, std::string name, Timestamp time)
{
    LogEntry entry;
    entry._isArrival = isArrival;
    entry._isEmployee = isEmployee;
    entry._name = name;
    entry._time = time;
}
LogEntry LogEntryFactory::create(bool isArrival, bool isEmployee, std::string name, Timestamp time, RoomID roomID)
{
    LogEntry entry = create(isArrival, isEmployee, name, time);
    entry._roomID = new RoomID(roomID);
}
#endif