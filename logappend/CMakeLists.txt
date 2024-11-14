# List all source files in the src directory
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# List all executables to add
add_executable(main "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp" ${SRC_FILES})

# List of all test executables
set(TEST_TARGETS
    main
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