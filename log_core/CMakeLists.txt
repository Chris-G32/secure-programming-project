cmake_minimum_required(VERSION 3.10)
project(log_core)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Define sources for the shared library
set(LOG_CORE_SOURCES
    src/gallery.cpp
    src/log_entry_factory.cpp
    src/log_entry.cpp
    src/log_file_stream.cpp
)

# Create the shared library
add_library(${PROJECT_NAME} SHARED ${LOG_CORE_SOURCES})

# Enable testing
enable_testing()

# Find and link Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Gather all test source files in the tests directory
file(GLOB TEST_SOURCES tests/*.cpp)

# Loop over each test source and create a test executable
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE) # Extract the test name (without extension)
    
    # Create an executable for each test source file
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    
    # Link the test executable with the shared library and Google Test
    target_link_libraries(${TEST_NAME} ${PROJECT_NAME} GTest::GTest GTest::Main)
    
    # Register each test with CTest
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
