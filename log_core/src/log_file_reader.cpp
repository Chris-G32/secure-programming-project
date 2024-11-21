#include "log_file/log_file_reader.hpp"
LogFile LogFileReader::load(std::istream &logStream, const std::string &key) const
{
    // Seek to the end of the stream to determine the size
    logStream.seekg(0, std::ios::end);
    size_t size = logStream.tellg();
    logStream.seekg(0, std::ios::beg);
    const size_t MINIMUM_FILE_SIZE = _cryptoProvider.HMAC_BYTES + _cryptoProvider.NONCE_BYTES + _cryptoProvider.KEY_BYTES;
    if (size < MINIMUM_FILE_SIZE)
    {
        throw std::runtime_error("Can not possibly be a stream representing a log file. Minimum size required is: " + std::to_string(MINIMUM_FILE_SIZE) + ", Stream size is: " + std::to_string(size) + "\n");
    }
    // Create a buffer with the appropriate size
    std::vector<unsigned char> buffer(size);
    // Read all the data into the buffer
    logStream.read(reinterpret_cast<char *>(buffer.data()), size);
    // Read in HMAC
    std::vector<unsigned char>
        hmac(_cryptoProvider.HMAC_BYTES);
    hmac.resize(_cryptoProvider.HMAC_BYTES);
    std::memcpy(hmac.data(), buffer.data() + buffer.size() - _cryptoProvider.HMAC_BYTES, _cryptoProvider.HMAC_BYTES);

    // Shorten buffer to remove hmac
    buffer.resize(buffer.size() - _cryptoProvider.HMAC_BYTES);
    if (!_cryptoProvider.isNotModified(buffer, hmac, key))
    {
        std::cout<<"integrity violation";
        throw std::runtime_error("Logfile has been tampered with!");
    }

    auto fileContents = _cryptoProvider.decrypt(buffer, key);

    // Ensure the read was successful
    if (!logStream)
    {
        throw std::runtime_error("Error reading from the input stream");
    }
    LogFile file(_entryParser, _cryptoProvider);
    file.loadRaw(fileContents, key);
    return file;
}
