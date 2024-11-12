#!/bin/bash

#Be sure to source the sourceme.sh file first
cd $SEC_PROG_PATH
cmake -B $SEC_PROG_BUILD_PATH -S $LOG_CORE_PATH
cd $SEC_PROG_BUILD_PATH
make