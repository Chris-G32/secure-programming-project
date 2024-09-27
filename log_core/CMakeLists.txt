add_library(log_core
    src/attendee.cpp
    src/gallery.cpp
    src/log_file.cpp
    src/main.cpp
)

target_include_directories(log_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)