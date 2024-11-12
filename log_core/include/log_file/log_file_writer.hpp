#ifndef LOG_FILE_WRITER
#define LOG_FILE_WRITER
#include "log_file.hpp"
#include "log_file_cryptography_provider.hpp"
#include <istream>
class ILogFileWriter
{
protected:
    const LogFileCryptographyProvider &_cryptoProvider;

public:
    ILogFileWriter(const LogFileCryptographyProvider &cryptoProvider) : _cryptoProvider(cryptoProvider) {}
    virtual void write(const Gallery &gallery, std::ostream &logStream, const std::string &key) const = 0;
};

class LogFileWriter : public ILogFileWriter
{
public:
    LogFileWriter(const LogFileCryptographyProvider &cryptoProvider) : ILogFileWriter(cryptoProvider) {}
    virtual void write(const Gallery &gallery, std::ostream &logStream, const std::string &key) const override;
};
#endif