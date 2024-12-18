#include "log_file_cryptography_provider.hpp"
#include "custom_string_utils.hpp"

std::vector<unsigned char> LogFileCryptographyProvider::decrypt(const std::vector<unsigned char> &rawFileData, const std::string &keyInput) const
{
    if (rawFileData.size() < KEY_BYTES + NONCE_BYTES)
    { // Minimum size: 8 bytes (nonce) + 32 bytes (key hash) + 64 bytes (HMAC)
        std::cerr << "File is too small! Is of size: " << rawFileData.size() << std::endl;
        throw std::runtime_error("File is too small.");
    }
    
    // Read nonce
    unsigned char nonce[NONCE_BYTES];
    std::memcpy(nonce, rawFileData.data(), NONCE_BYTES);
    // Read key hash
    unsigned char stored_key_hash[32];
    std::memcpy(stored_key_hash, rawFileData.data() + NONCE_BYTES, KEY_BYTES);

    // Read in encrypted contents
    std::vector<unsigned char> data(rawFileData.begin() + NONCE_BYTES + KEY_BYTES, rawFileData.end()); // -64 for HMAC

    // Verify key hash matches stored hash
    unsigned char computed_hashed_key[crypto_hash_sha256_BYTES];
    auto saltedKey = saltAndPepperEncryptionKey(keyInput);
    auto hashResult = crypto_hash_sha256(computed_hashed_key, STR_AS_UCHAR_STAR(saltedKey), saltedKey.size());
    bool hashesAreEqual = memcmp(stored_key_hash, computed_hashed_key, crypto_hash_sha256_BYTES) == 0;

    // Validate the key
    if (!hashesAreEqual)
    {
        throw std::runtime_error("Invalid key!");
    }
    crypto_stream_chacha20_xor(data.data(), data.data(), data.size(), nonce, hashText(keyInput).data());
    return data;
}

std::vector<unsigned char> LogFileCryptographyProvider::encrypt(const std::vector<unsigned char> &plaintextData, const std::string &key) const
{
    std::vector<unsigned char> buffer(plaintextData.size() + NONCE_BYTES + KEY_BYTES);
    const auto dataPortionOffset = NONCE_BYTES + KEY_BYTES;
    unsigned char nonce[NONCE_BYTES];
    randombytes_buf(nonce, NONCE_BYTES);
    crypto_stream_chacha20_xor(buffer.data() + dataPortionOffset, plaintextData.data(), plaintextData.size(), nonce, hashText(key).data());
    auto saltedKey = saltAndPepperEncryptionKey(key);
    crypto_hash_sha256(buffer.data() + NONCE_BYTES, STR_AS_UCHAR_STAR(saltedKey), saltedKey.size());
    memcpy(buffer.data(), nonce, NONCE_BYTES);
    return buffer;
}
bool LogFileCryptographyProvider::isNotModified(const std::vector<unsigned char> &text, const std::vector<unsigned char> &hmac, const std::string &key) const
{
    std::vector<unsigned char> keyHash(crypto_hash_sha256_BYTES);
    auto hmacKey = keyToHmacKey(key);
    crypto_hash_sha256(keyHash.data(), STR_AS_UCHAR_STAR(hmacKey), hmacKey.size());

    if (keyHash.size() != 32)
    {
        throw std::invalid_argument("Key must be exactly 32 bytes for HMAC");
    }
    // Validate the HMAC
    auto verifyResult =
        crypto_auth_hmacsha512_verify(
            hmac.data(), text.data(), text.size(), keyHash.data());
    return verifyResult == 0;
}

std::vector<unsigned char> LogFileCryptographyProvider::generateHMAC(const std::vector<unsigned char> &rawFileData, const std::string &key) const
{
    std::vector<unsigned char> keyHash(crypto_hash_sha256_BYTES);
    auto hmacKey = keyToHmacKey(key);
    crypto_hash_sha256(keyHash.data(), STR_AS_UCHAR_STAR(hmacKey), hmacKey.size());
    if (keyHash.size() != 32)
    {
        throw std::invalid_argument("Key must be exactly 32 bytes for HMAC");
    }
    std::vector<unsigned char> hmacBuffer(crypto_auth_hmacsha512_BYTES);
    crypto_auth_hmacsha512(hmacBuffer.data(), rawFileData.data(), rawFileData.size(), keyHash.data());
    return hmacBuffer;
}