# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug"

# Include any dependencies generated for this target.
include ezgl/CMakeFiles/EZGLib.dir/depend.make

# Include the progress variables for this target.
include ezgl/CMakeFiles/EZGLib.dir/progress.make

# Include the compile flags for this target's objects.
include ezgl/CMakeFiles/EZGLib.dir/flags.make

ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o: ezgl/CMakeFiles/EZGLib.dir/flags.make
ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o: ../ezgl/EZGL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o"
	cd "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug/ezgl" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EZGLib.dir/EZGL.cpp.o -c "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/ezgl/EZGL.cpp"

ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EZGLib.dir/EZGL.cpp.i"
	cd "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug/ezgl" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/ezgl/EZGL.cpp" > CMakeFiles/EZGLib.dir/EZGL.cpp.i

ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EZGLib.dir/EZGL.cpp.s"
	cd "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug/ezgl" && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/ezgl/EZGL.cpp" -o CMakeFiles/EZGLib.dir/EZGL.cpp.s

ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o.requires:

.PHONY : ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o.requires

ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o.provides: ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o.requires
	$(MAKE) -f ezgl/CMakeFiles/EZGLib.dir/build.make ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o.provides.build
.PHONY : ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o.provides

ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o.provides.build: ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o


# Object files for target EZGLib
EZGLib_OBJECTS = \
"CMakeFiles/EZGLib.dir/EZGL.cpp.o"

# External object files for target EZGLib
EZGLib_EXTERNAL_OBJECTS =

ezgl/libEZGLib.a: ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o
ezgl/libEZGLib.a: ezgl/CMakeFiles/EZGLib.dir/build.make
ezgl/libEZGLib.a: ezgl/CMakeFiles/EZGLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libEZGLib.a"
	cd "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug/ezgl" && $(CMAKE_COMMAND) -P CMakeFiles/EZGLib.dir/cmake_clean_target.cmake
	cd "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug/ezgl" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EZGLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ezgl/CMakeFiles/EZGLib.dir/build: ezgl/libEZGLib.a

.PHONY : ezgl/CMakeFiles/EZGLib.dir/build

ezgl/CMakeFiles/EZGLib.dir/requires: ezgl/CMakeFiles/EZGLib.dir/EZGL.cpp.o.requires

.PHONY : ezgl/CMakeFiles/EZGLib.dir/requires

ezgl/CMakeFiles/EZGLib.dir/clean:
	cd "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug/ezgl" && $(CMAKE_COMMAND) -P CMakeFiles/EZGLib.dir/cmake_clean.cmake
.PHONY : ezgl/CMakeFiles/EZGLib.dir/clean

ezgl/CMakeFiles/EZGLib.dir/depend:
	cd "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL" "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/ezgl" "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug" "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug/ezgl" "/Users/ocean/Documents/Codes/On Git/MultiPlatform-EZGL/cmake-build-debug/ezgl/CMakeFiles/EZGLib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : ezgl/CMakeFiles/EZGLib.dir/depend

