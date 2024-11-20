#ifndef LOG_FILE_READER
#define LOG_FILE_READER
#include "log_file.hpp"
#include "log_file_cryptography_provider.hpp"
#include <istream>
class ILogFileReader
{
protected:
    const LogEntryParser &_entryParser;
    const LogFileCryptographyProvider &_cryptoProvider;

public:
    ILogFileReader(const LogEntryParser &parser, const LogFileCryptographyProvider &cryptoProvider) : _entryParser(parser), _cryptoProvider(cryptoProvider) {}
    virtual LogFile load(std::istream &logStream, const std::string &key) const = 0;
};

class LogFileReader : public ILogFileReader
{
public:
    LogFileReader(const LogEntryParser &parser, const LogFileCryptographyProvider &cryptoProvider) : ILogFileReader(parser, cryptoProvider) {}
    virtual LogFile load(std::istream &logStream, const std::string &key) const override;
};
#endif