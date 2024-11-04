#ifndef LOG_ENTRY_STRING_VALIDATER_HPP
#define LOG_ENTRY_STRING_VALIDATER_HPP
#include <string>
#include "regex_utils.hpp"
class LogEntryStringValidater
{
private:
     LogEntryStringValidater() = default;
public:
    LogEntryStringValidater& instance()
    {
        static LogEntryStringValidater instance;
        return instance;
    }
    bool isValidName(const std::string &name)
    {
        return isAlphabetical(name);
    }
    bool isValidTimestamp(const std::string &timestamp)
    {
        return isNumeric(timestamp);
    }
};
#endif