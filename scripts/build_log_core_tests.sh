#!/bin/bash

#Be sure to source the sourceme.sh file first
cd $LOG_CORE_PATH
cmake .
cd $SEC_PROG_BUILD_PATH
cmake .
make