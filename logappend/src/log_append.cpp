#include "log_append.hpp"
#include <filesystem>
#include <optional>
#include "log_file_factory.hpp"
void LogAppend::process(std::ifstream &file)
{
    std::string line;
    int lineNum = 0;
    while (std::getline(file, line))
    {
        lineNum++;
        // Read line by line
        try
        {
            processAction(_actionParser.parse(line));
        }
        catch (...)
        {
            std::cerr << "Invalid command at line " << lineNum << " of " << _commandLineArgs[1] << std::endl;
        }
    }
}
void LogAppend::processAction(const LogAction &action)
{
    // Check if file exists
    // If it does exist load it from the file
    // If not create a file in memory
    /*============================================================*/
    bool fileIsCached = _logFiles.count(action.logFileName) > 0;
    auto logFileExists = std::filesystem::exists(action.logFileName);

    LogFile logFile = fileIsCached || logFileExists ? cachedLoad(action) : _logFileFactory.create(action.key);

    if (!fileIsCached)
    {
        _logFiles.insert(std::make_pair(action.logFileName, logFile));
    }

    auto gallery = logFile.authorizedGalleryGet(action.key);
    gallery.updateState(action.entry);
}

void LogAppend::process()
{
    if (isBatchFileCommand())
    {
        std::ifstream batchFile(_commandLineArgs[1]); // This will be the file path
        if (!batchFile.is_open())
        {
            exit(255);
        }
        process(batchFile);
        return;
    }
    else
    {
        try
        {
            auto action = _actionParser.parse(_commandLineArgs);
            processAction(action);
        }
        catch (...)
        {
            exit(255);
        }
    }
}