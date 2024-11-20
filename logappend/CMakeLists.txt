cmake_minimum_required(VERSION 3.15)
project(secure-programming-project)

# Enable testing
include(CTest)
enable_testing()

# Add Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Add the cmake folder to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find required packages
find_package(sodium REQUIRED)
find_package(GTest REQUIRED)

# List all source files in the src directory
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# First, create the shared library
add_library(logappend SHARED ${SRC_FILES})
target_include_directories(logappend
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../log_core/include  # Add log_core include path
    ${sodium_INCLUDE_DIR}
)
target_link_libraries(logappend 
    PRIVATE 
    sodium
    log_core  # Link against log_core if it's a separate library
)

# Then create the test executable
add_executable(log_append_tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/log_append_tests.cpp")
target_link_libraries(log_append_tests
    PRIVATE
    logappend
    sodium
    GTest::gtest
    GTest::gtest_main
    log_core  # Link against log_core if it's a separate library
)

# Add pthread on Unix systems
if(UNIX AND NOT APPLE)
    target_link_libraries(log_append_tests PRIVATE pthread)
endif()

# Add include directories for test
target_include_directories(log_append_tests
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../log_core/include  # Add log_core include path
    ${sodium_INCLUDE_DIR}
)

# Add test
add_test(NAME log_append_tests COMMAND log_append_tests)
gtest_discover_tests(log_append_tests)