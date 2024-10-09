#include <sodium.h>

int main()
{
    auto a = crypto_stream_chacha20_NONCEBYTES;
    unsigned char buf[12];
    auto key = (unsigned char *)"asd";
    crypto_stream_chacha20_xor(buf, buf, 12, buf, key);
    return a;
}
