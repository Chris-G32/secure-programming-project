#ifndef LOG_FILE_HPP
#define LOG_FILE_HPP
#include <ios>
#include <sodium.h>
#include <list>
#include <array>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include "log_entry.hpp"
#include "log_entry_parser.hpp"
#include "gallery.hpp"
class LogFile
{
private:
    std::string _key;
    unsigned char nonce[crypto_stream_chacha20_NONCEBYTES];
    // The raw file contents, without cryptographic related data
    std::vector<unsigned char> _rawFileContents;
    std::array<unsigned char, crypto_stream_chacha20_NONCEBYTES> readNonce();
    std::array<unsigned char, crypto_stream_chacha20_NONCEBYTES> readKeyHash();
    Gallery _gallery;
    // Provides us with the ability to parse the log entries from lines
    const LogEntryParser& _entryParser;
public:
    LogFile(const LogEntryParser& parser):_entryParser(parser){}
    /// @brief Loads a log file from its containing data
    /// @param rawFileData 
    /// @param key 
    void loadRaw(const std::vector<unsigned char>& rawFileData, const std::string &key);
    void save(const std::string& filePath){_gallery.saveToFile(filePath);}
};
#endif