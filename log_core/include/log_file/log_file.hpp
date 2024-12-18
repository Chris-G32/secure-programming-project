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
#include "log_file_cryptography_provider.hpp"
#include "gallery.hpp"

class LogFile
{
protected:
    std::vector<unsigned char> _keyHash;
    Gallery _gallery;
    // Provides us with the ability to parse the log entries from lines
    const LogEntryParser &_entryParser;
    const LogFileCryptographyProvider &_cryptoProvider;

public:
    LogFile(LogFile &rhs) : _entryParser(rhs._entryParser), _cryptoProvider(rhs._cryptoProvider), _keyHash(rhs._keyHash), _gallery(rhs._gallery)
    {
    }
    LogFile(LogFile &&other) : _entryParser(other._entryParser), _cryptoProvider(other._cryptoProvider)
    {
        _keyHash = std::move(other._keyHash);
        _gallery = std::move(other._gallery);
    }
    LogFile(const LogEntryParser &parser) : _entryParser(parser), _cryptoProvider(LogFileCryptographyProvider())
    {
    }
    LogFile(const LogEntryParser &parser, const LogFileCryptographyProvider &cryptoProvider) : _entryParser(parser), _cryptoProvider(cryptoProvider) {}
    LogFile(const LogEntryParser &parser, const LogFileCryptographyProvider &cryptoProvider, const std::string &key) : _entryParser(parser), _cryptoProvider(cryptoProvider)
    {
        _keyHash = _cryptoProvider.hashText(key);
    }
    /// @brief Loads a log file from its containing data
    /// @param rawFileData
    /// @param key
    void loadRaw(const std::vector<unsigned char> &rawFileData, const std::string &key);
    Gallery &authorizedGalleryGet(const std::string &key)
    {
        if (_keyHash.size() != 32)
        {
            std::runtime_error("Attempting to access logfile gallery before a load has been performed.");
        }
        auto hashedKey = _cryptoProvider.hashText(key);
        bool anyNotEqual = false;

        for (int i = 0; i < _cryptoProvider.KEY_BYTES; i++)
        {
            if (_keyHash[i] != hashedKey[i])
            {
                anyNotEqual = true;
            }
        }
        if (anyNotEqual)
        {
            throw std::runtime_error("Attempted unauthorized gallery access.");
        }
        return _gallery;
    }
    const Gallery &authorizedGalleryGet(const std::string &key) const
    {
        return authorizedGalleryGet(key);
    }
};
#endif