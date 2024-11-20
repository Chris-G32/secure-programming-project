#ifndef LOG_APPEND_HPP
#define LOG_APPEND_HPP
#include <fstream>
#include <unordered_map>
#include "log_file.hpp"
#include "log_file_reader.hpp"
#include "log_file_writer.hpp"
#include "log_entry_command_line_parser.hpp"
#include "log_file_factory.hpp"
class LogAppend
{
private:
    LogActionParser _actionParser;
    LogFileWriter _fileWriter;
    LogFileFactory _logFileFactory;
    /// @brief Command line args passed to program, without executable name
    const std::vector<std::string> _commandLineArgs;
    const uint MAX_ARGC = 11;
    void process(std::ifstream &file);
    std::unordered_map<std::string, LogFile> _logFiles;
    // Loads assocciated file from filesystem or memory if cached
    
    void processAction(const LogAction &action);

public:
    LogAppend(const int argc, const char **argv) : _logFileFactory(LogFileEntryParser::instance(), LogFileCryptographyProvider()), _fileWriter(LogFileCryptographyProvider()), _actionParser(MAX_ARGC - 1) //-1 to adjust for the fact that prog name is first arg passed
    {

        if (argc > MAX_ARGC)
        {
            exit(255);
        }
        for (int i = 1; i < argc; i++)
        {
            const_cast<std::vector<std::string> &>(_commandLineArgs).push_back(argv[i]);
        }
    }
    bool isBatchFileCommand()
    {
        if (_commandLineArgs.size() == 2)
        {
            return _commandLineArgs[0] == "-B";
        }
        return false;
    }
    /// @brief Runs the command provided in constructor.
    void process();
};
#endif