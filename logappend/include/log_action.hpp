#ifndef LOG_ACTION_HPP
#define LOG_ACTION_HPP
#include "log_entry.hpp"
#include <string>
struct LogAction
{
    LogEntry entry;
    std::string key;
    std::string logFileName;
};

#endif