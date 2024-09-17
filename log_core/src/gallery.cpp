#include "gallery.hpp"
#include "log_file_stream.hpp"
#include "actions.hpp"
#include <stdexcept>
using std::ifstream;
using std::ofstream;
using std::string;
Gallery::Gallery(const string &logFilePath, const string &key)
{
    ILogFileStream logReader(key, logFilePath);
    while (!logReader.eof())
    {
        LogEntry entry = logReader.getNextEntry();
        Attendee attendee(entry);
        auto toModify = _gallery.find(attendee);
        if (toModify == _gallery.end())
        {
            if (!entry.isArrivalToGallery())
            {
                throw std::runtime_error("First mention of attendee was not an arrival to gallery. Invalid log state");
            }
            EventLog log(entry.getTimestamp());
            _gallery.insert(std::make_pair(attendee, EventLog(entry.getTimestamp())));
        }
        entry.getAction().apply(toModify->second);
    }
}
const unsigned char *Gallery::getKeyDigest() const
{
    static bool firstPass = true;
    static unsigned char keyDigest[crypto_stream_chacha20_KEYBYTES];
    if (!firstPass)
        crypto_generichash(keyDigest, crypto_stream_chacha20_KEYBYTES, (unsigned char *)_key.c_str(), _key.length(), NULL, 0);
    return keyDigest;
}
void Gallery::saveToFile()
{
    if (!_fileExists)
    {
        // Generate nonce
    }
    ofstream outputFile(_fileName);
    // Output Nonce
    outputFile.write((char *)_nonce, crypto_stream_chacha20_NONCEBYTES);

    // Output digest
    auto digest = getKeyDigest();

    outputFile.write((const char *)digest, crypto_stream_chacha20_KEYBYTES);

    // Output logs
}
Gallery::~Gallery()
{
    saveToFile();
}