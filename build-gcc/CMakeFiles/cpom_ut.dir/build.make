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
include CMakeFiles/cpom_ut.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cpom_ut.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cpom_ut.dir/flags.make

CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o: CMakeFiles/cpom_ut.dir/flags.make
CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o: ../test/ClosestPointQuery.ut.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/dev/cpom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o -c /home/vincent/dev/cpom/test/ClosestPointQuery.ut.cpp

CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/dev/cpom/test/ClosestPointQuery.ut.cpp > CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.i

CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/dev/cpom/test/ClosestPointQuery.ut.cpp -o CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.s

CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o.requires:

.PHONY : CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o.requires

CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o.provides: CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o.requires
	$(MAKE) -f CMakeFiles/cpom_ut.dir/build.make CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o.provides.build
.PHONY : CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o.provides

CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o.provides.build: CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o


CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o: CMakeFiles/cpom_ut.dir/flags.make
CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o: ../test/OctreeNode.ut.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/dev/cpom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o -c /home/vincent/dev/cpom/test/OctreeNode.ut.cpp

CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/dev/cpom/test/OctreeNode.ut.cpp > CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.i

CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/dev/cpom/test/OctreeNode.ut.cpp -o CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.s

CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o.requires:

.PHONY : CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o.requires

CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o.provides: CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o.requires
	$(MAKE) -f CMakeFiles/cpom_ut.dir/build.make CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o.provides.build
.PHONY : CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o.provides

CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o.provides.build: CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o


CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o: CMakeFiles/cpom_ut.dir/flags.make
CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o: ../test/TestDriver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vincent/dev/cpom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o -c /home/vincent/dev/cpom/test/TestDriver.cpp

CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vincent/dev/cpom/test/TestDriver.cpp > CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.i

CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vincent/dev/cpom/test/TestDriver.cpp -o CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.s

CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o.requires:

.PHONY : CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o.requires

CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o.provides: CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o.requires
	$(MAKE) -f CMakeFiles/cpom_ut.dir/build.make CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o.provides.build
.PHONY : CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o.provides

CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o.provides.build: CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o


# Object files for target cpom_ut
cpom_ut_OBJECTS = \
"CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o" \
"CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o" \
"CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o"

# External object files for target cpom_ut
cpom_ut_EXTERNAL_OBJECTS =

cpom_ut: CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o
cpom_ut: CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o
cpom_ut: CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o
cpom_ut: CMakeFiles/cpom_ut.dir/build.make
cpom_ut: libcpom.a
cpom_ut: CMakeFiles/cpom_ut.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vincent/dev/cpom/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable cpom_ut"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cpom_ut.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cpom_ut.dir/build: cpom_ut

.PHONY : CMakeFiles/cpom_ut.dir/build

CMakeFiles/cpom_ut.dir/requires: CMakeFiles/cpom_ut.dir/test/ClosestPointQuery.ut.cpp.o.requires
CMakeFiles/cpom_ut.dir/requires: CMakeFiles/cpom_ut.dir/test/OctreeNode.ut.cpp.o.requires
CMakeFiles/cpom_ut.dir/requires: CMakeFiles/cpom_ut.dir/test/TestDriver.cpp.o.requires

.PHONY : CMakeFiles/cpom_ut.dir/requires

CMakeFiles/cpom_ut.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cpom_ut.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cpom_ut.dir/clean

CMakeFiles/cpom_ut.dir/depend:
	cd /home/vincent/dev/cpom/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vincent/dev/cpom /home/vincent/dev/cpom /home/vincent/dev/cpom/build /home/vincent/dev/cpom/build /home/vincent/dev/cpom/build/CMakeFiles/cpom_ut.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cpom_ut.dir/depend
