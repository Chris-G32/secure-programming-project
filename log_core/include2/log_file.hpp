#ifndef LOG_FILE_HPP
#define LOG_FILE_HPP
#include "sodium.h"
#include <list>
class LogFile
{
private:
    unsigned char _key[crypto_stream_chacha20_KEYBYTES];
    unsigned char _nonce[crypto_stream_chacha20_NONCEBYTES];
    // Logentry list
public:
};
#endif