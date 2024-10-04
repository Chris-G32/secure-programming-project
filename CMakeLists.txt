cmake_minimum_required(VERSION 3.15)
project(secure-programming-project)

# Enable testing
include(CTest)

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
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Add the cmake folder to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find libsodium
find_package(sodium REQUIRED) 
# The REQUIRED flag means CMake will error out if it can't find libsodium

# link libsodium
target_link_libraries(YourExecutableName PRIVATE sodium)

# Include directories for libsodium
target_include_directories(YourExecutableName PRIVATE ${sodium_INCLUDE_DIR})

# Add subdirectories
add_subdirectory(log_core)
add_subdirectory(logappend)
add_subdirectory(logread)

# If you want to add tests later, you can uncomment these lines and adjust the paths
# add_executable(logappend_tests path/to/logappend_tests.cpp)
# target_link_libraries(logappend_tests gtest_main log_core)

# add_executable(logread_tests path/to/slogread_tests.cpp)
# target_link_libraries(logread_tests gtest_main log_core)
# include(GoogleTest)
# gtest_discover_tests(logappend_tests)
# gtest_discover_tests(logread_tests)

# cd into build then cmake ..   -    then make - make clean - make VERBOSE=1 will so exaclty what make it doing wiht compiler