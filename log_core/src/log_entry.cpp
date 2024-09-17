#include "../include/log_entry.hpp"
#include "../include/regex_utils.hpp"
#include <stdexcept>

/// @brief Validates a string conversion and sets the time.
/// @param timeStr The string to convert
void LogEntry::setTimeFromString(const string &timeStr)
{
    const Timestamp MAX_TIMESTAMP = 1073741823U;
    if (!isNumeric(timeStr) || timeStr.length() > 10)
    {
        // TODO: Custom error for failure to set a logentry value
        throw std::runtime_error("Invalid Timestamp String");
    }
    char **end;
    unsigned long timestamp = std::strtoul(timeStr.c_str(), end, 10);
    if (timestamp > MAX_TIMESTAMP || timestamp < 1)
    {
        throw std::overflow_error("Timestamp is outside of acceptable range.");
    }
    _time = timestamp;
}
void LogEntry::setNameFromString(const string &nameStr)
{
    if (!isAlphabetical(nameStr))
    {
        // TODO: Custom error for failure to set a logentry value
        throw std::runtime_error("Invalid name String");
    }
    _name = nameStr;
}
void LogEntry::setRoomIDFromString(const string &roomIDStr)
{
    const RoomID MAX_ROOM_ID = 1073741823U;
    if (!isNumeric(roomIDStr) || roomIDStr.length() > 10)
    {
        // TODO: Custom error for failure to set a logentry value
        throw std::runtime_error("Invalid Room ID String");
    }
    char **end;
    unsigned long roomID = std::strtoul(roomIDStr.c_str(), end, 10);
    if (roomID > MAX_ROOM_ID)
    {
        throw std::overflow_error("Room ID is outside of acceptable range.");
    }
    _roomID = new RoomID(roomID);
}