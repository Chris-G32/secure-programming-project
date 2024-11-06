#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP
#include <string>
#include <vector>
#include <algorithm>
namespace StringUtils
{
    /// @brief Splits a string by spaces
    /// @param str
    /// @param maxBufferSize
    /// @return The vector of split string, if it is one longer than maxBufferSize, the last element will be the remainder of the string.
    std::vector<std::string> splitStringByDelimiter(const std::string &str, const char delimiter, const size_t maxBufferSize = 0)
    {
        if (str.empty())
        {
            return {};
        }
        std::vector<std::string> result;
        auto start = str.begin();
        size_t count = 0;
        while (start != str.end() && (maxBufferSize == 0 || count < maxBufferSize))
        {
            // Find the first space or end of the string
            auto end = std::find(start, str.end(), delimiter);

            // Add the substring between start and end
            result.push_back(std::string(start, end));

            // Move start to the next character after the space (or to the end)
            start = (end == str.end()) ? end : end + 1;
            count++;
        }
        // If there is still more string left, add it to the end
        if (start != str.end())
        {
            result.push_back(std::string(start, str.end()));
        }
        return result;
    }

}

#endif