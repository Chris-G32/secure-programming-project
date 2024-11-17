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
    using namespace std::filesystem;
    // Check if file exists
    // If it does exist load it from the file
    // If not create a file in memory
    /*============================================================*/
    bool fileIsCached = _logFiles.count(action.logFileName) > 0;
    auto logFileExists = exists(action.logFileName);

    if (!fileIsCached)
    {
        if(logFileExists)
        {
            std::ifstream logFileStream(action.logFileName);
            _logFiles.emplace(action.logFileName, _logFileFactory.create(logFileStream, action.key));
        }
        else
        {
            _logFiles.emplace(action.logFileName, _logFileFactory.create(action.key));
        }
    }

    _logFiles.at(action.logFileName).authorizedGalleryGet(action.key).updateState(action.entry);
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
            std::cout << "Received valid formatted action\n";
            processAction(action);
            auto logFile = _logFiles.at(action.logFileName);
            std::ofstream file(action.logFileName);
            _fileWriter.write(logFile.authorizedGalleryGet(action.key), file, action.key);
            file.close();
            std::cout << "Successfully process action\n";
        }
        catch (std::exception &e)
        {
            std::cerr << "Invalid command: " << e.what() << std::endl;
            exit(255);
        }
    }
}