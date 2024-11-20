#include <iostream>
#include "log_append.hpp"

int main(int argc, const char **argv)
{
    std::cout<<"Hello World\n";
    LogAppend logAppender(argc, argv);
    logAppender.process();
}