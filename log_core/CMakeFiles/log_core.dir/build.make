# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/chris/ksu-projects/secure-programming-project/log_core

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/chris/ksu-projects/secure-programming-project/log_core

# Include any dependencies generated for this target.
include CMakeFiles/log_core.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/log_core.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/log_core.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/log_core.dir/flags.make

CMakeFiles/log_core.dir/src/gallery.cpp.o: CMakeFiles/log_core.dir/flags.make
CMakeFiles/log_core.dir/src/gallery.cpp.o: src/gallery.cpp
CMakeFiles/log_core.dir/src/gallery.cpp.o: CMakeFiles/log_core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chris/ksu-projects/secure-programming-project/log_core/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/log_core.dir/src/gallery.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/log_core.dir/src/gallery.cpp.o -MF CMakeFiles/log_core.dir/src/gallery.cpp.o.d -o CMakeFiles/log_core.dir/src/gallery.cpp.o -c /home/chris/ksu-projects/secure-programming-project/log_core/src/gallery.cpp

CMakeFiles/log_core.dir/src/gallery.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_core.dir/src/gallery.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chris/ksu-projects/secure-programming-project/log_core/src/gallery.cpp > CMakeFiles/log_core.dir/src/gallery.cpp.i

CMakeFiles/log_core.dir/src/gallery.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_core.dir/src/gallery.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chris/ksu-projects/secure-programming-project/log_core/src/gallery.cpp -o CMakeFiles/log_core.dir/src/gallery.cpp.s

CMakeFiles/log_core.dir/src/attendee.cpp.o: CMakeFiles/log_core.dir/flags.make
CMakeFiles/log_core.dir/src/attendee.cpp.o: src/attendee.cpp
CMakeFiles/log_core.dir/src/attendee.cpp.o: CMakeFiles/log_core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chris/ksu-projects/secure-programming-project/log_core/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/log_core.dir/src/attendee.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/log_core.dir/src/attendee.cpp.o -MF CMakeFiles/log_core.dir/src/attendee.cpp.o.d -o CMakeFiles/log_core.dir/src/attendee.cpp.o -c /home/chris/ksu-projects/secure-programming-project/log_core/src/attendee.cpp

CMakeFiles/log_core.dir/src/attendee.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_core.dir/src/attendee.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chris/ksu-projects/secure-programming-project/log_core/src/attendee.cpp > CMakeFiles/log_core.dir/src/attendee.cpp.i

CMakeFiles/log_core.dir/src/attendee.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_core.dir/src/attendee.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chris/ksu-projects/secure-programming-project/log_core/src/attendee.cpp -o CMakeFiles/log_core.dir/src/attendee.cpp.s

CMakeFiles/log_core.dir/src/log_file.cpp.o: CMakeFiles/log_core.dir/flags.make
CMakeFiles/log_core.dir/src/log_file.cpp.o: src/log_file.cpp
CMakeFiles/log_core.dir/src/log_file.cpp.o: CMakeFiles/log_core.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/chris/ksu-projects/secure-programming-project/log_core/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/log_core.dir/src/log_file.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/log_core.dir/src/log_file.cpp.o -MF CMakeFiles/log_core.dir/src/log_file.cpp.o.d -o CMakeFiles/log_core.dir/src/log_file.cpp.o -c /home/chris/ksu-projects/secure-programming-project/log_core/src/log_file.cpp

CMakeFiles/log_core.dir/src/log_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/log_core.dir/src/log_file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/chris/ksu-projects/secure-programming-project/log_core/src/log_file.cpp > CMakeFiles/log_core.dir/src/log_file.cpp.i

CMakeFiles/log_core.dir/src/log_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/log_core.dir/src/log_file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/chris/ksu-projects/secure-programming-project/log_core/src/log_file.cpp -o CMakeFiles/log_core.dir/src/log_file.cpp.s

# Object files for target log_core
log_core_OBJECTS = \
"CMakeFiles/log_core.dir/src/gallery.cpp.o" \
"CMakeFiles/log_core.dir/src/attendee.cpp.o" \
"CMakeFiles/log_core.dir/src/log_file.cpp.o"

# External object files for target log_core
log_core_EXTERNAL_OBJECTS =

liblog_core.so: CMakeFiles/log_core.dir/src/gallery.cpp.o
liblog_core.so: CMakeFiles/log_core.dir/src/attendee.cpp.o
liblog_core.so: CMakeFiles/log_core.dir/src/log_file.cpp.o
liblog_core.so: CMakeFiles/log_core.dir/build.make
liblog_core.so: CMakeFiles/log_core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/chris/ksu-projects/secure-programming-project/log_core/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library liblog_core.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/log_core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/log_core.dir/build: liblog_core.so
.PHONY : CMakeFiles/log_core.dir/build

CMakeFiles/log_core.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/log_core.dir/cmake_clean.cmake
.PHONY : CMakeFiles/log_core.dir/clean

CMakeFiles/log_core.dir/depend:
	cd /home/chris/ksu-projects/secure-programming-project/log_core && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/chris/ksu-projects/secure-programming-project/log_core /home/chris/ksu-projects/secure-programming-project/log_core /home/chris/ksu-projects/secure-programming-project/log_core /home/chris/ksu-projects/secure-programming-project/log_core /home/chris/ksu-projects/secure-programming-project/log_core/CMakeFiles/log_core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/log_core.dir/depend

