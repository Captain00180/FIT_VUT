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
CMAKE_SOURCE_DIR = /home/filipjanuska/Desktop/IVS_Projekt_1/assignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/filipjanuska/Desktop/IVS_Projekt_1

# Utility rule file for pack.

# Include the progress variables for this target.
include CMakeFiles/pack.dir/progress.make

CMakeFiles/pack:
	/usr/bin/cmake -E tar cfv xlogin00.zip --format=zip /home/filipjanuska/Desktop/IVS_Projekt_1/assignment/black_box_tests.cpp /home/filipjanuska/Desktop/IVS_Projekt_1/assignment/white_box_tests.cpp /home/filipjanuska/Desktop/IVS_Projekt_1/assignment/tdd_code.h /home/filipjanuska/Desktop/IVS_Projekt_1/assignment/tdd_code.cpp

pack: CMakeFiles/pack
pack: CMakeFiles/pack.dir/build.make

.PHONY : pack

# Rule to build all files generated by this target.
CMakeFiles/pack.dir/build: pack

.PHONY : CMakeFiles/pack.dir/build

CMakeFiles/pack.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pack.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pack.dir/clean

CMakeFiles/pack.dir/depend:
	cd /home/filipjanuska/Desktop/IVS_Projekt_1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/filipjanuska/Desktop/IVS_Projekt_1/assignment /home/filipjanuska/Desktop/IVS_Projekt_1/assignment /home/filipjanuska/Desktop/IVS_Projekt_1 /home/filipjanuska/Desktop/IVS_Projekt_1 /home/filipjanuska/Desktop/IVS_Projekt_1/CMakeFiles/pack.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pack.dir/depend

