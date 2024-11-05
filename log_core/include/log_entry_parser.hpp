#ifndef LOG_ENTRY_PARSER_HPP
#define LOG_ENTRY_PARSER_HPP
#include "log_entry.hpp"
class LogEntryParser
{
protected:
    Timestamp getTimeFromString(const std::string &timeStr){
        const Timestamp MAX_TIMESTAMP = 1073741823U;
        if (!isNumeric(timeStr) || timeStr.length() > 10)
        {
            throw std::runtime_error("Invalid Timestamp String");
        }
        auto timestamp= std::strtoul(timeStr.c_str(), nullptr, 10);
        if (timestamp > MAX_TIMESTAMP || timestamp < 1)
        {
            throw std::overflow_error("Timestamp is outside of acceptable range.");
        }
        return timestamp;
    }
    bool getIsEmployeeFromString(const std::string &isEmployeeStr){
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
    bool getIsArrivalFromString(const std::string &isArrivalStr){
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
    // Returns a reference to the 
    bool isValidName(const std::string &nameStr){
        if (!isAlphabetical(nameStr)||nameStr.length()==0)
        {
            return false;
        }
        return true;
    }
    RoomID getRoomIDFromString(const std::string &roomIDStr){
        const Timestamp MAX_ROOM_ID = 1073741823U;
        if (!isNumeric(roomIDStr) || roomIDStr.length() > 10)
        {
            throw std::runtime_error("Invalid RoomID String");
        }
        auto roomID= std::strtoul(roomIDStr.c_str(), nullptr, 10);
        if (roomID > MAX_ROOM_ID)
        {
            throw std::overflow_error("Timestamp is outside of acceptable range.");
        }
        return roomID;
    }
public:
    virtual LogEntry parse(const std::string& entryString) const= 0;
    LogEntryParser(/* args */);
    ~LogEntryParser();
    std::pair<bool, LogEntry> tryParseFromCommandLineFormat(const std::string &line);
    std::pair<bool, LogEntry> tryParseFromFileFormat(const std::string &line);
    std::pair<bool, std::string> validateName(const std::string &line);
    LogEntry parseFromFileFormat(const std::string &line);
    // std::string toFileFormat(const LogEntry &entry);
    // std::string toFileFormat(const std::list<LogEntry> &entries);
    // std::string toFileFormat(const Gallery &gallery);
};
class LogFileEntryParser : public LogEntryParser
{
    public:
    LogEntry parse(const std::string& entryString) const override{
        LogEntry entry;
        std::vector<std::string> buffer(5);
        auto it=entryString.begin();
        while(it!=entryString.end()){
            auto spaceIt=std::find(it, entryString.end(), ' ');
            
        }

    }
};
#endif  