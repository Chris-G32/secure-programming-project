#include <iostream>
#include "log_read.hpp"
int main(int argc, const char **argv)
{
    LogRead logRead(argc, argv);
    logRead.process();
    return 0;
}