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
include BasicCamera/CMakeFiles/BasicCamera.dir/depend.make

# Include the progress variables for this target.
include BasicCamera/CMakeFiles/BasicCamera.dir/progress.make

# Include the compile flags for this target's objects.
include BasicCamera/CMakeFiles/BasicCamera.dir/flags.make

BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.o: BasicCamera/CMakeFiles/BasicCamera.dir/flags.make
BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.o: ../BasicCamera/src/BasicCamera/FreeLookCamera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.o"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.o -c /home/filipjanuska/Desktop/IZG/izgProject/BasicCamera/src/BasicCamera/FreeLookCamera.cpp

BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.i"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/filipjanuska/Desktop/IZG/izgProject/BasicCamera/src/BasicCamera/FreeLookCamera.cpp > CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.i

BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.s"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/filipjanuska/Desktop/IZG/izgProject/BasicCamera/src/BasicCamera/FreeLookCamera.cpp -o CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.s

BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.o: BasicCamera/CMakeFiles/BasicCamera.dir/flags.make
BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.o: ../BasicCamera/src/BasicCamera/OrbitCamera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.o"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.o -c /home/filipjanuska/Desktop/IZG/izgProject/BasicCamera/src/BasicCamera/OrbitCamera.cpp

BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.i"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/filipjanuska/Desktop/IZG/izgProject/BasicCamera/src/BasicCamera/OrbitCamera.cpp > CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.i

BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.s"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/filipjanuska/Desktop/IZG/izgProject/BasicCamera/src/BasicCamera/OrbitCamera.cpp -o CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.s

BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.o: BasicCamera/CMakeFiles/BasicCamera.dir/flags.make
BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.o: ../BasicCamera/src/BasicCamera/PerspectiveCamera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.o"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.o -c /home/filipjanuska/Desktop/IZG/izgProject/BasicCamera/src/BasicCamera/PerspectiveCamera.cpp

BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.i"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/filipjanuska/Desktop/IZG/izgProject/BasicCamera/src/BasicCamera/PerspectiveCamera.cpp > CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.i

BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.s"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/filipjanuska/Desktop/IZG/izgProject/BasicCamera/src/BasicCamera/PerspectiveCamera.cpp -o CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.s

# Object files for target BasicCamera
BasicCamera_OBJECTS = \
"CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.o" \
"CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.o" \
"CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.o"

# External object files for target BasicCamera
BasicCamera_EXTERNAL_OBJECTS =

BasicCamera/libBasicCamerad.a: BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/FreeLookCamera.cpp.o
BasicCamera/libBasicCamerad.a: BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/OrbitCamera.cpp.o
BasicCamera/libBasicCamerad.a: BasicCamera/CMakeFiles/BasicCamera.dir/src/BasicCamera/PerspectiveCamera.cpp.o
BasicCamera/libBasicCamerad.a: BasicCamera/CMakeFiles/BasicCamera.dir/build.make
BasicCamera/libBasicCamerad.a: BasicCamera/CMakeFiles/BasicCamera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libBasicCamerad.a"
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && $(CMAKE_COMMAND) -P CMakeFiles/BasicCamera.dir/cmake_clean_target.cmake
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BasicCamera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
BasicCamera/CMakeFiles/BasicCamera.dir/build: BasicCamera/libBasicCamerad.a

.PHONY : BasicCamera/CMakeFiles/BasicCamera.dir/build

BasicCamera/CMakeFiles/BasicCamera.dir/clean:
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera && $(CMAKE_COMMAND) -P CMakeFiles/BasicCamera.dir/cmake_clean.cmake
.PHONY : BasicCamera/CMakeFiles/BasicCamera.dir/clean

BasicCamera/CMakeFiles/BasicCamera.dir/depend:
	cd /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/filipjanuska/Desktop/IZG/izgProject /home/filipjanuska/Desktop/IZG/izgProject/BasicCamera /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera /home/filipjanuska/Desktop/IZG/izgProject/cmake-build-debug/BasicCamera/CMakeFiles/BasicCamera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : BasicCamera/CMakeFiles/BasicCamera.dir/depend

