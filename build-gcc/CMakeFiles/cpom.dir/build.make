# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vincent/dev/cpom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vincent/dev/cpom/build

# Include any dependencies generated for this target.
include CMakeFiles/cpom.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpom.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpom.dir/flags.make

CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o: CMakeFiles/cpom.dir/flags.make
CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o: ../src/ClosestPointQuery.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/dev/cpom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o -c /home/vincent/dev/cpom/src/ClosestPointQuery.cpp

CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/dev/cpom/src/ClosestPointQuery.cpp > CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.i

CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/dev/cpom/src/ClosestPointQuery.cpp -o CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.s

CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o.requires:

.PHONY : CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o.requires

CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o.provides: CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o.requires
	$(MAKE) -f CMakeFiles/cpom.dir/build.make CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o.provides.build
.PHONY : CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o.provides

CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o.provides.build: CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o


# Object files for target cpom
cpom_OBJECTS = \
"CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o"

# External object files for target cpom
cpom_EXTERNAL_OBJECTS =

libcpom.a: CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o
libcpom.a: CMakeFiles/cpom.dir/build.make
libcpom.a: CMakeFiles/cpom.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vincent/dev/cpom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libcpom.a"
	$(CMAKE_COMMAND) -P CMakeFiles/cpom.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpom.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpom.dir/build: libcpom.a

.PHONY : CMakeFiles/cpom.dir/build

CMakeFiles/cpom.dir/requires: CMakeFiles/cpom.dir/src/ClosestPointQuery.cpp.o.requires

.PHONY : CMakeFiles/cpom.dir/requires

CMakeFiles/cpom.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpom.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpom.dir/clean

CMakeFiles/cpom.dir/depend:
	cd /home/vincent/dev/cpom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vincent/dev/cpom /home/vincent/dev/cpom /home/vincent/dev/cpom/build /home/vincent/dev/cpom/build /home/vincent/dev/cpom/build/CMakeFiles/cpom.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpom.dir/depend

