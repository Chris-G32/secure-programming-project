#ifndef LOG_FILE_FACTORY_HPP
#define LOG_FILE_FACTORY_HPP
#include "log_file.hpp"
#include "log_file_reader.hpp"
class LogFileFactory
{
private:
    const LogEntryParser &_entryParser;
    const LogFileCryptographyProvider &_cryptoProvider;

public:
    LogFileFactory(const LogEntryParser &parser, const LogFileCryptographyProvider &cryptoProvider) : _entryParser(parser), _cryptoProvider(cryptoProvider) {}
    // Allows keys to be provided for log files that have just been created
    LogFile create(const std::string &key) { return LogFile(_entryParser, _cryptoProvider, key); }
    LogFile create() { return LogFile(_entryParser, _cryptoProvider); }
    LogFile create(std::istream &logStream, const std::string &key)
    {
        const LogFileReader _fileReader(_entryParser, _cryptoProvider);
        return _fileReader.load(logStream, key);
    }
};
#endif