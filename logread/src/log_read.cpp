#include "log_read.hpp"
#include "log_query_action_parser.hpp"
#include <filesystem>
void LogRead::process()
{
    using namespace std::filesystem;
    // Check if file exists
    // If it does exist load it from the file
    // If not create a file in memory
    /*============================================================*/
    try
    {
        LogQueryActionParser parser;
        auto action = parser.parse(_commandLineArgs);
        auto logFileExists = exists(action->logFileName);
        if (logFileExists)
        {
            std::ifstream logFileStream(action->logFileName);
            auto logFile=_logFileFactory.create(logFileStream, action->key);
            action->execute(logFile.authorizedGalleryGet(action->key));
            delete action;
        }
        else
        {
            std::cerr << "integrity violation";
            exit(255);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "invalid";
        exit(255);
    }
}