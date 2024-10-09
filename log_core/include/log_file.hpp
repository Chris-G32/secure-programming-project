#ifndef LOG_FILE_HPP
#define LOG_FILE_HPP
#include <sodium.h>
#include "log_entry.hpp"
#include <list>
#include <array>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include "gallery.hpp"
class LogFile
{
private:
    // unsigned char _key[crypto_stream_chacha20_KEYBYTES];
    std::string _fileName;
    std::string _key;
    std::list<LogEntry> _entries;
    std::array<unsigned char, crypto_stream_chacha20_NONCEBYTES> readNonce();
    std::array<unsigned char, crypto_stream_chacha20_NONCEBYTES> readKeyHash();

public:
    Gallery getGallery() { return Gallery(_entries); }
    LogFile(const std::string &fileName, const std::string &key);
    bool open() noexcept {}
};
#endif