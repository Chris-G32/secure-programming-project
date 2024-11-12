#include "log_file_writer.hpp"
#include "log_entry_factory.hpp"
#include <algorithm>
void LogFileWriter::write(const Gallery &gallery, std::ostream &logStream, const std::string &key) const
{
    if (gallery.getGalleryState().empty())
    {
        throw std::runtime_error("Empty galleries are not written, it would be an empty logfile.\n");
    }
    auto state = gallery.getGalleryState();
    LogEntryFactory factory;
    // Multiply by 5 to assume 5 events min per attendee
    auto estimatedGallerySize = gallery.getGalleryState().size() * 5;
    std::vector<LogEntry> entries(estimatedGallerySize);

    for (const auto &entryInfo : state)
    {
        Attendee attendee = entryInfo.first;

        for (auto &info : entryInfo.second.first)
        {
            entries.push_back(factory.create(info, attendee));
        }
    }

    auto timePredicate = [](const LogEntry &lhs, const LogEntry &rhs)
    { return lhs.getTime() < rhs.getTime(); };
    std::sort(entries.begin(), entries.end(), timePredicate);
    bool writeNewline = false;
    std::ostringstream ss;
    for (const auto &event : entries)
    {
        if (writeNewline)
        {
            writeNewline = true;
            ss << "\n";
        }
        ss << event.toFileFormat();
    }
    auto fileString = ss.str();
    std::vector<unsigned char> fileVector(fileString.begin(), fileString.end());
    auto encrypted = _cryptoProvider.encrypt(fileVector, key);
    fileVector.clear();
    auto hmac = _cryptoProvider.generateHMAC(encrypted, key);
    encrypted.insert(encrypted.end(), hmac.begin(), hmac.end());
    for (const auto &i : encrypted)
    {
        logStream << i;
    }
}
