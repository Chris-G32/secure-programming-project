cmake_minimum_required(VERSION 3.15)
project(ParentProject)

# Enable testing
include(CTest)

# Add subdirectories for each project
add_subdirectory(log_core)
# add_subdirectory(logappend)
# add_subdirectory(logread)
# add_subdirectory(Project3)
