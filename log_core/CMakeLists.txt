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
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the cmake folder to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Find libsodium
find_package(sodium REQUIRED)
# Find Google Test
find_package(GTest REQUIRED)

# Add the executable
add_executable(gallery_event_tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/gallery_event_tests.cpp")

add_executable(gallery_tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/gallery_tests.cpp")

# List of all test executables
set(TEST_TARGETS
    gallery_event_tests
    gallery_tests
)

# Apply settings to all test executables
foreach(target ${TEST_TARGETS})
    # Link libraries
    target_link_libraries(${target}
        PRIVATE
        sodium
        GTest::gtest
        GTest::gtest_main
    )

    # Add pthread on Unix systems
    if(UNIX AND NOT APPLE)
        target_link_libraries(${target} PRIVATE pthread)
    endif()

    # Add include directories
    target_include_directories(${target}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${sodium_INCLUDE_DIR}
    )

    # Add test
    add_test(NAME ${target} COMMAND ${target})
    gtest_discover_tests(${target})
endforeach()

# Print some debug information
# message(STATUS "sodium_INCLUDE_DIR: ${sodium_INCLUDE_DIR}")
# message(STATUS "Project source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
# message(STATUS "Test file location: ${CMAKE_CURRENT_SOURCE_DIR}/tests/gallery_event_tests.cpp")