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
include MealyMachine/CMakeFiles/MealyMachine.dir/depend.make

# Include the progress variables for this target.
include MealyMachine/CMakeFiles/MealyMachine.dir/progress.make

# Include the compile flags for this target's objects.
include MealyMachine/CMakeFiles/MealyMachine.dir/flags.make

MealyMachine/CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.o: MealyMachine/CMakeFiles/MealyMachine.dir/flags.make
MealyMachine/CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.o: ../MealyMachine/src/MealyMachine/MealyMachine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object MealyMachine/CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.o"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/MealyMachine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.o -c /home/filipjanuska/Desktop/IZG/izgProject/MealyMachine/src/MealyMachine/MealyMachine.cpp

MealyMachine/CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.i"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/MealyMachine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/filipjanuska/Desktop/IZG/izgProject/MealyMachine/src/MealyMachine/MealyMachine.cpp > CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.i

MealyMachine/CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.s"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/MealyMachine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/filipjanuska/Desktop/IZG/izgProject/MealyMachine/src/MealyMachine/MealyMachine.cpp -o CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.s

# Object files for target MealyMachine
MealyMachine_OBJECTS = \
"CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.o"

# External object files for target MealyMachine
MealyMachine_EXTERNAL_OBJECTS =

MealyMachine/libMealyMachined.a: MealyMachine/CMakeFiles/MealyMachine.dir/src/MealyMachine/MealyMachine.cpp.o
MealyMachine/libMealyMachined.a: MealyMachine/CMakeFiles/MealyMachine.dir/build.make
MealyMachine/libMealyMachined.a: MealyMachine/CMakeFiles/MealyMachine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libMealyMachined.a"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/MealyMachine && $(CMAKE_COMMAND) -P CMakeFiles/MealyMachine.dir/cmake_clean_target.cmake
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/MealyMachine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MealyMachine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
MealyMachine/CMakeFiles/MealyMachine.dir/build: MealyMachine/libMealyMachined.a

.PHONY : MealyMachine/CMakeFiles/MealyMachine.dir/build

MealyMachine/CMakeFiles/MealyMachine.dir/clean:
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/MealyMachine && $(CMAKE_COMMAND) -P CMakeFiles/MealyMachine.dir/cmake_clean.cmake
.PHONY : MealyMachine/CMakeFiles/MealyMachine.dir/clean

MealyMachine/CMakeFiles/MealyMachine.dir/depend:
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/filipjanuska/Desktop/IZG/izgProject /home/filipjanuska/Desktop/IZG/izgProject/MealyMachine /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/MealyMachine /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/MealyMachine/CMakeFiles/MealyMachine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : MealyMachine/CMakeFiles/MealyMachine.dir/depend

