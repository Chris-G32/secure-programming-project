add_executable(logread
    logread.cpp
)

target_link_libraries(logread PRIVATE log_core)