#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP
#include <vector>
#include <string>
namespace StringUtils
{
    /// @brief Splits string like data at spaces.
    /// @tparam T A type that can be iterated through using the for(char val:container) syntax.
    /// @param charVec The container of our string information
    /// @return A vector of string split on spaces.
    template <class T>
    std::vector<std::string> splitAtSpaces(const T &charVec)
    {
        std::vector<std::string> result;
        std::string currentString;

        for (char ch : charVec)
        {
            if (ch == ' ')
            {
                // If we hit a space and have accumulated a string, push it to the result
                if (!currentString.empty())
                {
                    result.push_back(currentString);
                    currentString.clear(); // Clear the string for the next word
                }
            }
            else
            {
                // Otherwise, accumulate the characters in the current string
                currentString += ch;
            }
        }

        // Push the last string if there was no trailing space
        if (!currentString.empty())
        {
            result.push_back(currentString);
        }

        return result;
    }
}

#endif