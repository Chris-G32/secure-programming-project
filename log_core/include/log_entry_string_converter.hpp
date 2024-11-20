#ifndef LOG_ENTRY_STRING_CONVERTER_HPP
#define LOG_ENTRY_STRING_CONVERTER_HPP
#include "log_entry.hpp"
#include "utils/regex_utils.hpp"
class LogEntryStringConverter
{
private:
    LogEntryStringConverter() = default;

public:
    static LogEntryStringConverter &instance()
    {
        static LogEntryStringConverter instance;
        return instance;
    }
    Timestamp getTimeFromString(const std::string &timeStr) const
    {
        const Timestamp MAX_TIMESTAMP = 1073741823U;
        if (!RegexUtils::isNumeric(timeStr) || timeStr.length() > 10)
        {
            throw std::runtime_error("Invalid Timestamp String");
        }
        auto timestamp = std::strtoul(timeStr.c_str(), nullptr, 10);
        if (timestamp > MAX_TIMESTAMP || timestamp < 1)
        {
            throw std::overflow_error("Timestamp is outside of acceptable range.");
        }
        return timestamp;
    }
    bool getIsEmployeeFromString(const std::string &isEmployeeStr) const
    {
        if (isEmployeeStr == "E")
        {
            return true;
        }
        else if (isEmployeeStr == "G")
        {
            return false;
        }
        else
        {
            throw std::invalid_argument("Invalid string for isEmployee");
        }
    }
    bool getIsArrivalFromString(const std::string &isArrivalStr) const
    {
        if (isArrivalStr == "A")
        {
            return true;
        }
        else if (isArrivalStr == "L")
        {
            return false;
        }
        else
        {
            throw std::invalid_argument("Invalid string for isArrival");
        }
    }

    bool isValidName(const std::string &nameStr) const
    {
        if (!RegexUtils::isAlphabetical(nameStr) || nameStr.length() == 0)
        {
            return false;
        }
        return true;
    }
    RoomID getRoomIDFromString(const std::string &roomIDStr) const
    {
        const Timestamp MAX_ROOM_ID = 1073741823U;
        if (!RegexUtils::isNumeric(roomIDStr) || roomIDStr.length() > 10)
        {
            throw std::runtime_error("Invalid RoomID String");
        }
        auto roomID = std::strtoul(roomIDStr.c_str(), nullptr, 10);
        if (roomID > MAX_ROOM_ID)
        {
            throw std::overflow_error("Timestamp is outside of acceptable range.");
        }
        return roomID;
    }
};
#endif