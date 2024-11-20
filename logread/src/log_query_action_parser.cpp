#include "log_query_action_parser.hpp"
#include <set>
#include "regex_utils.hpp"
#include <functional>
#include "log_read_flags.hpp"
LogQueryAction *LogQueryActionParser::parse(const std::vector<std::string> &actionArgs)
{
    const std::runtime_error malformedCommandError("Received a malformed logentry command. Must follow the form of -T <timestamp> -K <token> (-E <employee-name> | -G <guest-name>) (-A | -L) [-R <room-id>] <log>");
    if (actionArgs.size() > 6 || actionArgs.size() < 4)
    {
        throw malformedCommandError;
    }
    std::set<char>
        flagsSeenSet;
    auto it = actionArgs.begin();
    LogQueryAction *action = nullptr;
    std::string key;
    std::function<LogQueryAction *(const std::string ,const std::string)> buildQueryAction;
    while (it != actionArgs.end()-1)
    {
        std::string flagStringWithDash = *it;
        if (flagStringWithDash.size() != 2)
        {
            throw malformedCommandError;
        }
        const std::regex flagRegex("^-[KRS]$");
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
        flagsSeenSet.insert(flagCharacter);
        //Advance past flag
        it++;

        switch (flagCharacter)
        {
        case ROOM_QUERY_FLAG:
        {
            if (flagsSeenSet.count(STATE_QUERY_FLAG) > 0)
            {
                throw malformedCommandError;
            }
            const std::regex guestOrEmployeeFlagRegex("^-[EG]$");
            // Arg after room query flag must be guest or employee flag
            auto guestOrEmployee = *it;
            if (!std::regex_match(guestOrEmployee, guestOrEmployeeFlagRegex))
            {
                throw malformedCommandError;
            }
            // Advance past guest or employee flag to name argument
            std::advance(it, 1);
            auto name = *it;
            if (!RegexUtils::isAlphabetical(name))
            {
                throw malformedCommandError;
            }
            Attendee attendee(name, guestOrEmployee[1] == EMPLOYEE_FLAG);
            buildQueryAction = [attendee](const std::string key,const std::string logFileName) -> LogQueryAction *
            {
                return new RoomsQueryAction(logFileName, key, attendee);
            };
            it++;// Advance past name argument
            break;
        }
        case STATE_QUERY_FLAG:
        {
            if (flagsSeenSet.count(ROOM_QUERY_FLAG) > 0)
            {
                throw malformedCommandError;
            }
            buildQueryAction = [](const std::string key,const std::string logFileName) -> LogQueryAction *
            {
                return new StateQueryAction(logFileName, key);
            };
            break;
        }
        case KEY_FLAG:
        {
            if (!RegexUtils::isAlphaNumeric(*it))
            {
                throw malformedCommandError;
            }
            key = *it;
            it++;
            break;
        }
        default:
        {
            throw malformedCommandError;
        }
        }

    }
    auto logFileName = *it;
    return buildQueryAction(key,logFileName);
}