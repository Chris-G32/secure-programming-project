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

# Find libsodium
find_package(sodium REQUIRED)
# Find Google Test
find_package(GTest REQUIRED)


# Add subdirectories for each project
add_subdirectory(log_core)
add_subdirectory(logappend)
#add_subdirectory(logread)

