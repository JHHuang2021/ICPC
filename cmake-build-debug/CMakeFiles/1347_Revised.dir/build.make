# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/d/CLionProjects/ICPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/CLionProjects/ICPC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/1347_Revised.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/1347_Revised.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1347_Revised.dir/flags.make

CMakeFiles/1347_Revised.dir/1347_Revised.cpp.o: CMakeFiles/1347_Revised.dir/flags.make
CMakeFiles/1347_Revised.dir/1347_Revised.cpp.o: ../1347_Revised.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/CLionProjects/ICPC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1347_Revised.dir/1347_Revised.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/1347_Revised.dir/1347_Revised.cpp.o -c /mnt/d/CLionProjects/ICPC/1347_Revised.cpp

CMakeFiles/1347_Revised.dir/1347_Revised.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1347_Revised.dir/1347_Revised.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/CLionProjects/ICPC/1347_Revised.cpp > CMakeFiles/1347_Revised.dir/1347_Revised.cpp.i

CMakeFiles/1347_Revised.dir/1347_Revised.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1347_Revised.dir/1347_Revised.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/CLionProjects/ICPC/1347_Revised.cpp -o CMakeFiles/1347_Revised.dir/1347_Revised.cpp.s

# Object files for target 1347_Revised
1347_Revised_OBJECTS = \
"CMakeFiles/1347_Revised.dir/1347_Revised.cpp.o"

# External object files for target 1347_Revised
1347_Revised_EXTERNAL_OBJECTS =

1347_Revised: CMakeFiles/1347_Revised.dir/1347_Revised.cpp.o
1347_Revised: CMakeFiles/1347_Revised.dir/build.make
1347_Revised: CMakeFiles/1347_Revised.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/CLionProjects/ICPC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 1347_Revised"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/1347_Revised.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1347_Revised.dir/build: 1347_Revised

.PHONY : CMakeFiles/1347_Revised.dir/build

CMakeFiles/1347_Revised.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/1347_Revised.dir/cmake_clean.cmake
.PHONY : CMakeFiles/1347_Revised.dir/clean

CMakeFiles/1347_Revised.dir/depend:
	cd /mnt/d/CLionProjects/ICPC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/CLionProjects/ICPC /mnt/d/CLionProjects/ICPC /mnt/d/CLionProjects/ICPC/cmake-build-debug /mnt/d/CLionProjects/ICPC/cmake-build-debug /mnt/d/CLionProjects/ICPC/cmake-build-debug/CMakeFiles/1347_Revised.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1347_Revised.dir/depend

