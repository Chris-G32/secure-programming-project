#ifndef LOG_QUERY_ACTION_HPP
#define LOG_QUERY_ACTION_HPP
#include "gallery.hpp"
#include "attendee.hpp"
#include "log_read_flags.hpp"
#include <string>

class LogQueryAction
{
protected:
    LogQueryAction(const std::string &logFileNameArg,const std::string& keyArg) : logFileName(logFileNameArg),key(keyArg) {}

public:
    std::string logFileName;
    std::string key;
    virtual void execute(const Gallery &gallery) = 0;
};
class RoomsQueryAction : public LogQueryAction
{
protected:
    Attendee _attendee;
public:
    RoomsQueryAction(const std::string &logFileNameArg,const std::string& keyArg, const Attendee &attendee) : LogQueryAction(logFileNameArg,keyArg),_attendee(attendee) {}
    virtual void execute(const Gallery &gallery) override;
};
class StateQueryAction : public LogQueryAction
{
public:
    StateQueryAction(const std::string &logFileNameArg,const std::string& keyArg) : LogQueryAction(logFileNameArg,keyArg) {}
    virtual void execute(const Gallery &gallery) override;
};
#endif