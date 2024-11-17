#!/bin/bash

# Set some env vars for our other scripts
# Define the environment variables
export SEC_PROG_PATH="/home/chris/coding_projects/secure-programming-project"
export LOG_CORE_PATH="${SEC_PROG_PATH}/log_core"
export LOG_APPEND_PATH="${SEC_PROG_PATH}/logappend"
export SEC_PROG_BUILD_PATH="${SEC_PROG_PATH}/build"
mkdir -p $SEC_PROG_BUILD_PATH
# Optional: Print the values to verify
echo "SEC_PROG_PATH is set to: $SEC_PROG_PATH"
echo "LOG_CORE_PATH is set to: $LOG_CORE_PATH"
echo "SEC_PROG_BUILD_PATH is set to: $SEC_PROG_BUILD_PATH"

runTests () {
    cd $SEC_PROG_BUILD_PATH
    # Can pass args to ctest
    ctest $1
}
runTestsVerbose(){
    runTests "--rerun-failed --output-on-failure"
}
buildProj(){
    cd $SEC_PROG_PATH/scripts
    bash build_log_core_tests.sh
}
buildAndTest(){
    buildProj
    runTests
}
buildAndTestVerbose(){
    buildProj
    runTests "--rerun-failed --output-on-failure"
}
buildLogAppend(){
    cd $SEC_PROG_PATH
    cmake -B build -S .
    cd build
    make
    cp logappend/logappend $SEC_PROG_PATH/executables
    cd $SEC_PROG_PATH/executables
    # cmake -B $LOG_APPEND_PATH -S $LOG_APPEND_PATH/build
    # cd $LOG_APPEND_PATH/build
    # make
}