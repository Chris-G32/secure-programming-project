#ifndef LOG_ENTRY_FACTORY_HPP
#define LOG_ENTRY_FACTORY_HPP
#include <string>
#include "log_entry.hpp"
#include <stdexcept>
/// @brief Factory for individual logEntries stored in our logFile
class LogEntryFactory
{
protected:
    /// @brief
    /// @return
    virtual uint getMaxArgCount() { return 8; }
    unsigned int getExpectedFlagIndex(char flag);
    void populateRoomID(LogEntry &entry, std::vector<std::string> args);
    void populateTimestamp(LogEntry &entry, std::vector<std::string> args);
    // void populateKey(LogEntry &entry, std::vector<std::string> args) { throw std::logic_error("Keys are not stored per entry in the log file."); }
    void populateNameAndIsEmployee(LogEntry &entry, std::vector<std::string> args);
    void populateAction(LogEntry &entry, std::vector<std::string> args);

public:
    LogEntryFactory() {}
    /// @brief Creates a log entry from a vector of flags and arguments.
    /// @param argc The length of the array args.
    /// @param args The array of string arguments
    /// @return A log entry object containing the data in args
    virtual LogEntry create(std::vector<std::string> args);
};
#endif