add_executable(logappend
    logappend.cpp
)

target_include_directories(logappend PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(logappend PRIVATE log_core)