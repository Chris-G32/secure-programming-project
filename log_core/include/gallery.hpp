#ifndef GALLERY_HPP
#define GALLERY_HPP
#include <map>
#include "attendee_state.hpp"
#include "attendee.hpp"
#include <string>
#include <iostream>
#include "typedefs.hpp"
#include "log_entry.hpp"
#include <fstream>
#include "sodium.h"
using std::string;
class Gallery
{
protected:
    std::map<Attendee, EventLog> _gallery; // NOTE: You cannot use the [] operator bc we do not want the event logs to be called without args ever.
    string _key;
    string _fileName;
    bool _fileExists;
    unsigned char _nonce[crypto_stream_chacha20_NONCEBYTES];
    void initLogFile(const std::string &key);
    const unsigned char *getKeyDigest() const;
    void saveToFile();

public:
    LogEntry entryFromLine(const std::string &);
    Gallery(const std::string &, const std::string &);
    ~Gallery();
};

#endif