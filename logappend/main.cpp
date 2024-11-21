#include <iostream>
#include "log_append.hpp"

int main(int argc, const char **argv)
{
    LogAppend logAppender(argc, argv);
    logAppender.process();
}