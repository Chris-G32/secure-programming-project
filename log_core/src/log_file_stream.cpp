#include "log_file_stream.hpp"
#include "log_entry_factory.hpp"
#include "string_utils.hpp"

ILogFileStream::ILogFileStream(const std::string &key, const std::string &fileName) : std::ifstream(fileName), _position(0)
{
    if (sodium_init() == -1)
    {
        throw std::runtime_error("Failed to load sodium library for encryption and decryption resources.");
    }
    // Load Nonce
    get((char *)_nonce, crypto_stream_chacha20_NONCEBYTES);
    if (eof() || fail())
    {
        throw std::runtime_error("Failed to read nonce.");
    }
    _position += crypto_stream_chacha20_NONCEBYTES;

    // Load key digest
    unsigned char keyDigestInFile[crypto_stream_chacha20_KEYBYTES];
    get((char *)keyDigestInFile, crypto_stream_chacha20_KEYBYTES);
    crypto_stream_chacha20_xor(keyDigestInFile, keyDigestInFile, crypto_stream_chacha20_KEYBYTES, _nonce, (unsigned char *)key.c_str());
    if (eof() || fail())
    {
        throw std::runtime_error("Failed to read keyDigest.");
    }
    _position += crypto_stream_chacha20_KEYBYTES;

    // Generate hash of provided digest
    unsigned char keyDigest[crypto_stream_chacha20_KEYBYTES];
    auto result = crypto_generichash(keyDigest, crypto_stream_chacha20_KEYBYTES, (unsigned char *)key.c_str(), key.length(), NULL, 0);

    // Validate hash
    bool digestMatches = true;
    for (int i = 0; i < crypto_stream_chacha20_KEYBYTES; i++)
    {
        if (keyDigest[i] != keyDigestInFile[i])
        {
            digestMatches = false;
        }
    }
    if (!digestMatches)
    {
        throw std::runtime_error("Invalid key.");
    }
}
LogEntry ILogFileStream::getNextEntry()
{
    std::vector<char> characters(50);
    char buffer;
    // Lambda to ensure order within while
    auto tryGet = [&buffer, this]()
    {
        get(buffer);
        return eof();
    };

    while (tryGet())
    {
        crypto_stream_chacha20_xor_ic((unsigned char *)buffer, (unsigned char *)buffer, 1, _nonce, _position, _key);
        if (buffer != '\n')
        {
            characters.push_back(buffer);
        }
        _position++;
    }
    static LogEntryFactory factory;
    std::vector<string> logArguments = StringUtils::splitAtSpaces(characters);
    return factory.create(logArguments);
}