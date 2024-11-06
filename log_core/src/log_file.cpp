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

void LogFile::loadRaw(const std::vector<unsigned char>& rawFileData, const std::string &key)
{
    using std::ifstream;
    if (sodium_init() == -1)
    {
        throw std::runtime_error("Failed to load sodium library for encryption and decryption resources.");
    }
    _key=key;
    //Validate the file data is of minimum size for crypto operations
    if (rawFileData.size() < 104)
    { // Minimum size: 8 bytes (nonce) + 32 bytes (key hash) + 64 bytes (HMAC)
        std::cerr << "File is too small!" << std::endl;
        throw std::runtime_error("File is too small.");
    }

    const auto NONCE_BYTES = crypto_stream_chacha20_NONCEBYTES;
    const auto KEY_BYTES = crypto_stream_chacha20_KEYBYTES;
    const auto HMAC_BYTES = crypto_auth_hmacsha512_BYTES;
    // Extract nonce, key hash, encrypted data, and HMAC
    unsigned char nonce[NONCE_BYTES];
    std::memcpy(nonce, rawFileData.data(), NONCE_BYTES);
    
    unsigned char hashed_key[32];
    std::memcpy(hashed_key, rawFileData.data() + NONCE_BYTES, KEY_BYTES);

    std::vector<unsigned char> encrypted_data(rawFileData.begin() + NONCE_BYTES + KEY_BYTES, rawFileData.end() - HMAC_BYTES); // -64 for HMAC

    unsigned char hmac[HMAC_BYTES];
    std::memcpy(hmac, rawFileData.data() + rawFileData.size() - HMAC_BYTES, HMAC_BYTES);

    // Validate the key
    if (!validate_key(hashed_key, (unsigned char *)key.c_str()))
    {
        throw std::runtime_error("Invalid key!");
    }
    // Validate the HMAC
    if (!validate_hmac(rawFileData, hmac, (unsigned char *)key.c_str()))
    {
        throw std::runtime_error("Mac does not match expected!");
    }
    // Then go through the data and decrypt it as we go, like in previous code
    _rawFileContents = decrypt_data(encrypted_data, nonce, (unsigned char *)key.c_str());
    std::string plaintext(_rawFileContents.begin(), _rawFileContents.end());
    _gallery = Gallery(_entryParser.parseMany(plaintext));
}
