# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/filipjanuska/Downloads/CLion-2019.3.5/clion-2019.3.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/filipjanuska/Downloads/CLion-2019.3.5/clion-2019.3.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/filipjanuska/Desktop/IZG/izgProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug

# Include any dependencies generated for this target.
include TxtUtils/CMakeFiles/TxtUtils.dir/depend.make

# Include the progress variables for this target.
include TxtUtils/CMakeFiles/TxtUtils.dir/progress.make

# Include the compile flags for this target's objects.
include TxtUtils/CMakeFiles/TxtUtils.dir/flags.make

TxtUtils/CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.o: TxtUtils/CMakeFiles/TxtUtils.dir/flags.make
TxtUtils/CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.o: ../TxtUtils/src/TxtUtils/TxtUtils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object TxtUtils/CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.o"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/TxtUtils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.o -c /home/filipjanuska/Desktop/IZG/izgProject/TxtUtils/src/TxtUtils/TxtUtils.cpp

TxtUtils/CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.i"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/TxtUtils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/filipjanuska/Desktop/IZG/izgProject/TxtUtils/src/TxtUtils/TxtUtils.cpp > CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.i

TxtUtils/CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.s"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/TxtUtils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/filipjanuska/Desktop/IZG/izgProject/TxtUtils/src/TxtUtils/TxtUtils.cpp -o CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.s

# Object files for target TxtUtils
TxtUtils_OBJECTS = \
"CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.o"

# External object files for target TxtUtils
TxtUtils_EXTERNAL_OBJECTS =

TxtUtils/libTxtUtilsd.a: TxtUtils/CMakeFiles/TxtUtils.dir/src/TxtUtils/TxtUtils.cpp.o
TxtUtils/libTxtUtilsd.a: TxtUtils/CMakeFiles/TxtUtils.dir/build.make
TxtUtils/libTxtUtilsd.a: TxtUtils/CMakeFiles/TxtUtils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libTxtUtilsd.a"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/TxtUtils && $(CMAKE_COMMAND) -P CMakeFiles/TxtUtils.dir/cmake_clean_target.cmake
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/TxtUtils && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TxtUtils.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TxtUtils/CMakeFiles/TxtUtils.dir/build: TxtUtils/libTxtUtilsd.a

.PHONY : TxtUtils/CMakeFiles/TxtUtils.dir/build

TxtUtils/CMakeFiles/TxtUtils.dir/clean:
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/TxtUtils && $(CMAKE_COMMAND) -P CMakeFiles/TxtUtils.dir/cmake_clean.cmake
.PHONY : TxtUtils/CMakeFiles/TxtUtils.dir/clean

TxtUtils/CMakeFiles/TxtUtils.dir/depend:
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/filipjanuska/Desktop/IZG/izgProject /home/filipjanuska/Desktop/IZG/izgProject/TxtUtils /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/TxtUtils /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/TxtUtils/CMakeFiles/TxtUtils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TxtUtils/CMakeFiles/TxtUtils.dir/depend

