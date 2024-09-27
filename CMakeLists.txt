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

# Add subdirectories
add_subdirectory(log_core)
add_subdirectory(logappend)
add_subdirectory(logread)

# If you want to add tests later, you can uncomment these lines and adjust the paths
# add_executable(log_entry_factory_tests path/to/log_entry_factory_tests.cpp)
# target_link_libraries(log_entry_factory_tests gtest_main log_core)
# add_executable(string_utils_tests path/to/string_utils_tests.cpp)
# target_link_libraries(string_utils_tests gtest_main log_core)
# include(GoogleTest)
# gtest_discover_tests(log_entry_factory_tests)
# gtest_discover_tests(string_utils_tests)

# cd into build then cmake ..   -    then make - make clean - make VERBOSE=1 will so exaclty what make it doing wiht compiler