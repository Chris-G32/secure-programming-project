#ifndef LOG_READ_HPP
#define LOG_READ_HPP
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "log_file_factory.hpp"
#include "log_file.hpp"
#include "log_file_reader.hpp"
#include "log_file_writer.hpp"
class LogRead
{
private:
    const std::vector<std::string> _commandLineArgs;
    const uint MAX_ARGC = 11;
    LogFileWriter _fileWriter;
    LogFileFactory _logFileFactory;
    void process(std::ifstream &file);
public:
    LogRead(const int argc, const char **argv) : _logFileFactory(LogFileEntryParser::instance(), LogFileCryptographyProvider()), _fileWriter(LogFileCryptographyProvider()) //-1 to adjust for the fact that prog name is first arg passed
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
    void process();
};

#endif