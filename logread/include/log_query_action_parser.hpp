#ifndef LOG_QUERY_ACTION_PARSER_HPP
#define LOG_QUERY_ACTION_PARSER_HPP
#include "log_query_action.hpp"
#include <vector>
class LogQueryActionParser
{
    public:
    /// @brief 
    /// @param actionArgs 
    /// @return LogQueryAction* caller responsible for deletion of pointer. 
    LogQueryAction* parse(const std::vector<std::string> &actionArgs);
};
#endif