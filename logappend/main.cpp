#include <iostream>
#include "log_append.hpp"

int main(int argc, const char **argv)
{
    auto a = argc;
    LogAppend logAppender(argc, argv);
    logAppender.process();
}