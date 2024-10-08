#ifndef LOG_FILE_HPP
#define LOG_FILE_HPP
#include "sodium.h"
#include "log_entry.hpp"
#include <list>
#include <array>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
class LogFile
{
private:
    // unsigned char _key[crypto_stream_chacha20_KEYBYTES];
    std::string _fileName;
    std::string _key;
    std::vector<LogEntry> _entries;
    std::array<unsigned char, crypto_stream_chacha20_NONCEBYTES> readNonce();
    std::array<unsigned char, crypto_stream_chacha20_NONCEBYTES> readKeyHash();
    
public:
    LogFile(const std::string &fileName, const std::string &key);
    void addEntry(LogEntry newLog){ _entries.push_back(newLog);}
    bool open() noexcept {}
};
#endif