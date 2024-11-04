#ifndef LOG_ENTRY_PARSER_HPP
#define LOG_ENTRY_PARSER_HPP
#include "log_entry.hpp"
class LogEntryParser
{
public:
    LogEntryParser(/* args */);
    ~LogEntryParser();
    std::pair<bool, LogEntry> tryParseFromCommandLineFormat(const std::string &line);
    std::pair<bool, LogEntry> tryParseFromFileFormat(const std::string &line);
    std::pair<bool, std::string> validateName(const std::string &line);
    LogEntry parseFromFileFormat(const std::string &line);
    std::string toFileFormat(const LogEntry &entry);
    std::string toFileFormat(const std::list<LogEntry> &entries);
    std::string toFileFormat(const Gallery &gallery
};
#endif  