#ifndef LOG_ENTRY_PARSER_HPP
#define LOG_ENTRY_PARSER_HPP
#include "log_entry.hpp"
#include "log_entry_string_converter.hpp"
#include "utils/custom_string_utils.hpp"
#include <list>
class LogEntryParser
{
protected:
    LogEntryStringConverter &_converter = LogEntryStringConverter::instance();
    virtual LogEntry createFromArgumentVector(const std::vector<std::string> &logEntryArgs) const = 0;
    LogEntryParser() = default;

public:
    virtual LogEntry parse(const std::string &entryString) const = 0;
    /// @brief Parses a string of log entries into a list of LogEntries. Each line is an entry.
    /// @param entries String containing lines of entries.
    /// @return The parsed list of entries.
    virtual std::list<LogEntry> parseMany(const std::string &entries) const
    {
        std::vector<std::string> entryStrings = StringUtils::splitStringByDelimiter(entries, '\n');
        std::list<LogEntry> logEntries;
        for (auto &&entryString : entryStrings)
        {
            logEntries.push_back(parse(entryString));
        }
        return logEntries;
    }
    virtual ~LogEntryParser() = default;
};

class LogFileEntryParser : public LogEntryParser
{
private:
    LogFileEntryParser() {}

protected:
    /// @brief Takes a vector of strings and creates a LogEntry
    /// @param logEntryArgs A vector of strings, assumed to be of the lenght 4 or 5
    /// @return
    virtual LogEntry createFromArgumentVector(const std::vector<std::string> &logEntryArgs) const override
    {
        const int TIME_INDEX = 0;
        const int IS_EMPLOYEE_INDEX = 1;
        const int NAME_INDEX = 2;
        const int IS_ARRIVAL_INDEX = 3;
        const int ROOM_ID_INDEX = 4;
        if (!_converter.isValidName(logEntryArgs[NAME_INDEX]))
        {
            throw std::invalid_argument("Invalid name in log entry");
        }
        if (logEntryArgs.size() == 4)
        {
            return LogEntry(_converter.getIsArrivalFromString(logEntryArgs[IS_ARRIVAL_INDEX]),
                            _converter.getIsEmployeeFromString(logEntryArgs[IS_EMPLOYEE_INDEX]),
                            logEntryArgs[NAME_INDEX],
                            _converter.getTimeFromString(logEntryArgs[TIME_INDEX]));
        }
        else if (logEntryArgs.size() == 5)
        {
            return LogEntry(_converter.getIsArrivalFromString(logEntryArgs[IS_ARRIVAL_INDEX]),
                            _converter.getIsEmployeeFromString(logEntryArgs[IS_EMPLOYEE_INDEX]),
                            logEntryArgs[NAME_INDEX],
                            _converter.getTimeFromString(logEntryArgs[TIME_INDEX]),
                            _converter.getRoomIDFromString(logEntryArgs[ROOM_ID_INDEX]));
        }
        else
        {
            throw std::invalid_argument("Invalid number of arguments in log entry");
        }
    }

public:
    static LogEntryParser &instance()
    {
        static LogFileEntryParser instance;
        return instance;
    }

    LogEntry parse(const std::string &entryString) const override
    {
        const auto MAX_EXPECTED_LENGTH = 5;
        const auto MIN_EXPECTED_LENGTH = 4;
        const char SPACE_DELIMITER = ' ';
        // Validate that our argvector is not larger or shorter than expected
        std::vector<std::string> logEntryArgs = StringUtils::splitStringByDelimiter(entryString, SPACE_DELIMITER, MAX_EXPECTED_LENGTH);
        if (logEntryArgs.size() < MIN_EXPECTED_LENGTH || logEntryArgs.size() > MAX_EXPECTED_LENGTH)
        {
            throw std::invalid_argument("Invalid number of arguments in log entry");
        }
        return createFromArgumentVector(logEntryArgs);
    }
};
#endif