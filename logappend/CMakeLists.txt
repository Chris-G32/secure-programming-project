add_executable(log_file_tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/log_file_tests.cpp" ${SRC_FILES})

# List of all test executables
set(TEST_TARGETS
    gallery_event_tests
    gallery_tests
    log_entry_tests
    log_entry_parser_tests
    log_file_cryptography_provider_tests
    log_file_writer_tests
    log_file_reader_tests
    log_file_tests
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
        ${CMAKE_CURRENT_SOURCE_DIR}/include/factories
        ${CMAKE_CURRENT_SOURCE_DIR}/include/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/include/log_file
        ${sodium_INCLUDE_DIR}
    )

    # Add test
    add_test(NAME ${target} COMMAND ${target})
    gtest_discover_tests(${target})
endforeach()