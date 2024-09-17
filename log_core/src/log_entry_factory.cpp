#include "log_entry_factory.hpp"
#include <stdexcept>
#include <functional>
#include "regex_utils.hpp"
#include <vector>

// -T time -E|G name -A|L -R room logfile
//  0 1    2    3      4   5  6    7
unsigned int LogEntryFactory::getExpectedFlagIndex(char flag)
{
    switch (flag)
    {
    case 'T':
        return 0;
    case 'E':
    case 'G':
        return 2;
    case 'A':
    case 'L':
        return 4;
    case 'R':
        return 5;
    default:
        throw std::logic_error("Flag not supported");
    }
}
void LogEntryFactory::populateRoomID(LogEntry &entry, std::vector<std::string> args)
{
    const unsigned int expectedRoomFlagIndex = getExpectedFlagIndex('R');
    if (args[expectedRoomFlagIndex] != "-R")
    {
        throw std::runtime_error("Expected -R flag.");
    }
    std::string roomNumArg = args[expectedRoomFlagIndex + 1];
    if (!isNumeric(roomNumArg))
    {
        throw std::runtime_error("Non numeric RoomID provided");
    }
    char **end;
    const RoomID MAX_ROOM_ID = 1073741823U;
    unsigned long roomId = std::strtoul(roomNumArg.c_str(), end, 10);
    if (roomId > MAX_ROOM_ID)
    {
        throw std::overflow_error("RoomID is outside of acceptable range.");
    }
    entry._roomID = new RoomID(roomId);
}
void LogEntryFactory::populateTimestamp(LogEntry &entry, std::vector<std::string> args)
{
    const unsigned int expectedTimestampFlagIndex = getExpectedFlagIndex('T');

    if (args[expectedTimestampFlagIndex] != "-T")
    {
        throw std::runtime_error("Expected -T flag.");
    }
    std::string timestampArg = args[expectedTimestampFlagIndex + 1];
    if (!isNumeric(timestampArg))
    {
        throw std::runtime_error("Non numeric timestamp provided");
    }
    char **end;
    const Timestamp MAX_TIMESTAMP = 1073741823U;
    unsigned long timestamp = std::strtoul(timestampArg.c_str(), end, 10);
    if (timestamp > MAX_TIMESTAMP || timestamp < 1)
    {
        throw std::overflow_error("Timestamp is outside of acceptable range.");
    }
    entry._time = timestamp;
}

void LogEntryFactory::populateNameAndIsEmployee(LogEntry &entry, std::vector<std::string> args)
{
    // This line operates under the assumption that G and E will occupy the same index
    const unsigned int expectedNameFlagIndex = getExpectedFlagIndex('G');
    if (args[expectedNameFlagIndex] == "-G")
    {
        entry._isEmployee = false;
    }
    else if (args[expectedNameFlagIndex] == "-E")
    {
        entry._isEmployee = true;
    }
    else
    {
        throw std::runtime_error("Expected -G or -E flag.");
    }

    std::string nameArg = args[expectedNameFlagIndex + 1];
    if (!isAlphabetical(nameArg))
    {
        throw std::runtime_error("Invalid name provided. Must be alphabetical.");
    }
    entry._name = nameArg;
}
void LogEntryFactory::populateAction(LogEntry &entry, std::vector<std::string> args)
{
    // This line operates under the assumption that A and L will occupy the same index
    const unsigned int expectedActionFlagIndex = getExpectedFlagIndex('A');
    if (args[expectedActionFlagIndex] == "-A")
    {
        entry._isArrival = true;
    }
    else if (args[expectedActionFlagIndex] == "-L")
    {
        entry._isArrival = false;
    }
    else
    {
        throw std::runtime_error("Expected -A or -L flag.");
    }
}
/// @brief Converts a vector of strings of our specified format into a LogEntry object
/// @param args String vector containing information about the LogEntry
/// @return The LogEntry represented by the string.
LogEntry LogEntryFactory::create(std::vector<std::string> args)
{
    LogEntry entry;

    if (args.size() < 4 | args.size() > 5)
    {
        throw std::length_error("Invalid argument length for logentry");
    }
    if (args.size() == 5)
    {
        populateRoomID(entry, args);
    }
    populateTimestamp(entry, args);
    populateNameAndIsEmployee(entry, args);
    populateAction(entry, args);
}
