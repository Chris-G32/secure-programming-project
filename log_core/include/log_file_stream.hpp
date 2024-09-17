#ifndef LOG_FILE_STREAM_HPP
#define LOG_FILE_STREAM_HPP
#include <fstream>
#include <string>
#include "sodium.h"
#include <stdexcept>
#include "log_entry.hpp"
class ILogFileStream : private std::ifstream
{
private:
    unsigned char _key[crypto_stream_chacha20_KEYBYTES];
    unsigned char _nonce[crypto_stream_chacha20_NONCEBYTES];
    unsigned long long _position;

public:
    /// @brief Returns a copy of the nonce. IMPORTANT! Caller is responsible for deletion of memory
    /// @return Copy of the nonce used on the file.
    unsigned char *getNonceCopy()
    {
        auto copy = new unsigned char[crypto_stream_chacha20_NONCEBYTES];
        memcpy(copy, _nonce, crypto_stream_chacha20_NONCEBYTES);
        return copy;
    }
    using std::ifstream::eof;
    const unsigned char *getNonce() { return _nonce; }
    ILogFileStream(const std::string &key, const std::string &fileName);
    LogEntry getNextEntry();
};

#endif