#include "log_file.hpp"
#include <algorithm>
#include <numeric>
bool validate_hmac(const std::vector<unsigned char> &file_data, const unsigned char *hmac, const unsigned char *key)
{
    return crypto_auth_hmacsha512_verify(hmac, file_data.data(), file_data.size() - crypto_auth_hmacsha512_BYTES, key) == 0;
}

bool validate_key(const unsigned char *hashed_key, const unsigned char *input_key)
{
    unsigned char computed_hashed_key[crypto_hash_sha256_BYTES];
    crypto_hash_sha256(computed_hashed_key, input_key, crypto_secretbox_KEYBYTES); // Assuming input key length is 32 bytes
    return memcmp(hashed_key, computed_hashed_key, crypto_hash_sha256_BYTES) == 0;
}

std::vector<unsigned char> decrypt_data(const std::vector<unsigned char> &ciphertext, const unsigned char *nonce, const unsigned char *key)
{
    std::vector<unsigned char> decrypted_data(ciphertext.size());
    crypto_stream_chacha20_xor(decrypted_data.data(), ciphertext.data(), ciphertext.size(), nonce, key);
    return decrypted_data;
}
LogFile::LogFile(const std::string &fileName, const std::string &key) : _fileName(fileName), _key(key)
{
    using std::ifstream;
    if (sodium_init() == -1)
    {
        throw std::runtime_error("Failed to load sodium library for encryption and decryption resources.");
    }
    std::ifstream file(fileName, std::ios::binary);
    if (!file)
    {
        // std::cerr << "Could not open the file!" << std::endl;
        throw std::runtime_error("File does not exist!");
    }

    // Read the file into a buffer
    std::vector<unsigned char> file_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    if (file_data.size() < 104)
    { // Minimum size: 8 bytes (nonce) + 32 bytes (key hash) + 64 bytes (HMAC)
        std::cerr << "File is too small!" << std::endl;
        throw std::runtime_error("File is too small.");
    }
    const auto NONCE_BYTES = crypto_stream_chacha20_NONCEBYTES;
    const auto KEY_BYTES = crypto_stream_chacha20_KEYBYTES;
    const auto HMAC_BYTES = crypto_auth_hmacsha512_BYTES;
    // Extract nonce, key hash, encrypted data, and HMAC
    unsigned char nonce[NONCE_BYTES];
    std::memcpy(nonce, file_data.data(), NONCE_BYTES);

    unsigned char hashed_key[32];
    std::memcpy(hashed_key, file_data.data() + NONCE_BYTES, KEY_BYTES);

    std::vector<unsigned char> encrypted_data(file_data.begin() + NONCE_BYTES + KEY_BYTES, file_data.end() - HMAC_BYTES); // -64 for HMAC

    unsigned char hmac[HMAC_BYTES];
    std::memcpy(hmac, file_data.data() + file_data.size() - HMAC_BYTES, HMAC_BYTES);

    // Validate the key
    if (!validate_key(hashed_key, (unsigned char *)key.c_str()))
    {
        throw std::runtime_error("Invalid key!");
    }
    // Validate the HMAC
    if (!validate_hmac(file_data, hmac, (unsigned char *)key.c_str()))
    {
        throw std::runtime_error("Mac does not match expected!");
    }
    // Then go through the data and decrypt it as we go, like in previous code
    std::vector<unsigned char> plaintext = decrypt_data(encrypted_data, nonce, (unsigned char *)key.c_str());
    std::vector<std::string> entryStrings(40);
    for (auto it = plaintext.begin(); it != plaintext.end();)
    {
        auto newLine = std::find_if(it, plaintext.end(), [](unsigned char data)
                                    { return data == '\n'; });
        std::string string(it, newLine);
        entryStrings.push_back(std::move(string));
        it = newLine;
    }
    
    // Pass entry strings to a function to populate our entrues
    //  _entries= //JACKS FUNCTION
    for (auto &&line : entryStrings)
    {
        //needs to follow the ctor for LogEntry
        //LogEntry(std::string time, std::string name, bool isEmployee, bool isArrival)
        LogEntry entry(); // = JACKS FUNCTION
        LogFile::addEntry(entry);
    }
}
