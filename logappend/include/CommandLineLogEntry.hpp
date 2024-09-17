#ifndef COMMAND_LINE_LOG_ENTRY_HPP
#define COMMAND_LINE_LOG_ENTRY_HPP
#include <string>
#include <regex>
#include "../../log_core/include/log_entry.hpp"
#include "typedefs.hpp"
class CommandLineLogEntry : LogEntry
{
private:
    std::string _key;

protected:
    std::string getKey() { return _key; }

public:
    friend class LogEntryFactory;
    /// @brief Returns a copy of the key and deletes the currently stored key from the object. This is to try to keep the key ephemeral.
    /// @return The key
    std::string consumeKey()
    {
        std::string copy(_key);
        _key.clear();
        return copy;
    }
};

#endif