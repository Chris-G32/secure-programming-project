#ifndef REGEX_UTILS_HPP
#define REGEX_UTILS_HPP
#include <regex>
#include <string>
namespace RegexUtils
{
    inline bool isNumeric(const std::string &toCheck)
    {
        static const std::regex isNum(R"([0-9]+)");
        return std::regex_match(toCheck, isNum);
    }
    inline bool isAlphaNumeric(const std::string &toCheck)
    {
        static const std::regex isAlNum(R"([a-zA-Z0-9]+)");
        return std::regex_match(toCheck, isAlNum);
    }
    inline bool isAlphabetical(const std::string &toCheck)
    {
        static const std::regex isAlphabet(R"([a-zA-Z]+)");
        return std::regex_match(toCheck, isAlphabet);
    }
    inline bool isValidLogFileName(const std::string &toCheck)
    {
        static const std::regex isAlnumPeriodOrUnderscore(R"([a-zA-z0-9._]+)");
        return std::regex_match(toCheck, isAlnumPeriodOrUnderscore);
    }
}
#endif