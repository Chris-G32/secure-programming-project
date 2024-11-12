#include "log_file/log_file.hpp"
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

void LogFile::loadRaw(const std::vector<unsigned char> &rawFileData, const std::string &key)
{
    _keyHash = _cryptoProvider.hashText(key);
    // Then go through the data and decrypt it as we go, like in previous code
    std::string plaintext(rawFileData.begin(), rawFileData.end());
    _gallery = Gallery(_entryParser.parseMany(plaintext));
}
