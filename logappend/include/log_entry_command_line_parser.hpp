#ifndef LOG_ENTRY_COMMAND_LINE_PARSER_HPP
#define LOG_ENTRY_COMMAND_LINE_PARSER_HPP
#include "log_action.hpp"
#include "log_entry_string_converter.hpp"
#include "custom_string_utils.hpp"
#include "log_entry_factory.hpp"
#include "regex_utils.hpp"
#include <set>
#include <regex>
#include "log_append_flags.hpp"
class LogActionParser
{
private:
    const uint MAX_ALLOWED_ACTION_ARGS_LENGTH;
    const uint MIN_ALLOWED_ACTION_ARGS_LENGTH = 8;

public:
    LogActionParser(const uint maxArgsLength = 10) : MAX_ALLOWED_ACTION_ARGS_LENGTH(maxArgsLength) {}
    LogAction parse(const std::vector<std::string> &actionArgs)
    {
        const std::runtime_error malformedCommandError("Received a malformed logentry command. Must follow the form of -T <timestamp> -K <token> (-E <employee-name> | -G <guest-name>) (-A | -L) [-R <room-id>] <log>");
        if (actionArgs.size() > MAX_ALLOWED_ACTION_ARGS_LENGTH || actionArgs.size() < MIN_ALLOWED_ACTION_ARGS_LENGTH)
        {
            throw malformedCommandError;
        }
        std::set<char>
            flagsSeenSet;
        auto it = actionArgs.begin();
        LogAction action;

        auto strConverter = LogEntryStringConverter::instance();
        while (it != actionArgs.end() - 1)
        {
            std::string flagStringWithDash = *it;
            if (flagStringWithDash.size() != 2)
            {
                throw malformedCommandError;
            }
            std::regex flagRegex("^-[KTALEGR]$");
            if (!std::regex_match(flagStringWithDash, flagRegex))
            {
                throw malformedCommandError;
            };
            // We know the flag is of length 2 so this is safe.
            char flagCharacter = flagStringWithDash.at(1);

            // No repeat flags
            if (flagsSeenSet.count(flagCharacter) > 0)
            {
                throw malformedCommandError;
            }
            std::advance(it, 1);
            switch (flagCharacter)
            {
            case KEY_FLAG:
                if (!RegexUtils::isAlphaNumeric(*it))
                {
                    throw new std::runtime_error("Key arguments must be alphanumeric.");
                }
                action.key = *it;
                std::advance(it, 1);
                break;
            case TIME_FLAG:
                action.entry.setTime(strConverter.getTimeFromString(*it));
                std::advance(it, 1);
                break;
            case EMPLOYEE_FLAG: // Shares guest flag operation
                if (flagsSeenSet.count(GUEST_FLAG) > 0)
                {
                    throw malformedCommandError;
                }
            case GUEST_FLAG:
                if (flagsSeenSet.count(EMPLOYEE_FLAG) > 0)
                {
                    throw malformedCommandError;
                }
                
                action.entry.setIsEmployee(strConverter.getIsEmployeeFromString({flagCharacter}));
                action.entry.setName(strConverter.isValidName(*it) ? *it : throw new std::runtime_error("Invalid name argument."));
                std::advance(it, 1);
                break;
            case ARRIVAL_FLAG:
                if (flagsSeenSet.count(LEAVE_FLAG) > 0)
                {
                    throw malformedCommandError;
                }
            case LEAVE_FLAG:
                if (flagsSeenSet.count(ARRIVAL_FLAG) > 0)
                {
                    throw malformedCommandError;
                }
                action.entry.setIsArrival(strConverter.getIsArrivalFromString({flagCharacter}));
                break;
            case ROOM_ID_FLAG:
                action.entry.setRoomID(strConverter.getRoomIDFromString(*it));
                std::advance(it, 1);
                break;
            default:
                throw malformedCommandError;
            }
            flagsSeenSet.insert(flagCharacter);
        }
        if (!RegexUtils::isValidLogFileName(*it))
        {
            throw malformedCommandError;
        }
        action.logFileName = *it;
        return action;
    }
    LogAction parse(const std::string &actionString)
    {
        auto commandArgs = StringUtils::splitStringByDelimiter(actionString, ' ', MAX_ALLOWED_ACTION_ARGS_LENGTH);
        return parse(commandArgs);
    }
};
#endif