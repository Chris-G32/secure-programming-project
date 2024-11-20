#include "log_append.hpp"
#include <filesystem>
#include <optional>
#include "log_file_factory.hpp"
void LogAppend::process(std::ifstream &file)
{
    std::string line;
    int lineNum = 0;
    std::unordered_map<std::string,std::string> logFileNameToKeys;
    while (std::getline(file, line))
    {
        lineNum++;
        // Read line by line
        try
        {
            auto action=_actionParser.parse(line);
            processAction(action);
            logFileNameToKeys[action.logFileName]=action.key;
        }
        catch (std::exception &e)
        {
            std::cerr << "Invalid command at line " << lineNum << " of " << _commandLineArgs[1] << std::endl;
        }
    }
    for(auto& logfile:_logFiles){
            auto name = logfile.first;
            auto logFile = logfile.second;
            std::ofstream file(logfile.first);
            _fileWriter.write(logFile.authorizedGalleryGet(logFileNameToKeys.at(name)), file, logFileNameToKeys.at(name));
            file.close();
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
            std::cout<<"invalid";
            exit(255);
        }
        try{
            process(batchFile);
        }
        catch(std::exception&e)
        {
            std::cerr << "Error processing batchfile. "<<e.what()<<"\n";
            batchFile.close();
            exit(255);
        }
        batchFile.close();
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
            std::cout<<"invalid";
            // std::cerr << "Invalid command: " << e.what() << std::endl;
            exit(255);
        }
    }
}