# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/agavrilenko/Coding/C++/CLion/CLion-2018.2.4/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/agavrilenko/Coding/C++/CLion/CLion-2018.2.4/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/agavrilenko/CLionProjects/Shell/Book_2.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/agavrilenko/CLionProjects/Shell/Book_2.0/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Book_2_0.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Book_2_0.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Book_2_0.dir/flags.make

CMakeFiles/Book_2_0.dir/main.cpp.o: CMakeFiles/Book_2_0.dir/flags.make
CMakeFiles/Book_2_0.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/agavrilenko/CLionProjects/Shell/Book_2.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Book_2_0.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Book_2_0.dir/main.cpp.o -c /home/agavrilenko/CLionProjects/Shell/Book_2.0/main.cpp

CMakeFiles/Book_2_0.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Book_2_0.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/agavrilenko/CLionProjects/Shell/Book_2.0/main.cpp > CMakeFiles/Book_2_0.dir/main.cpp.i

CMakeFiles/Book_2_0.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Book_2_0.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/agavrilenko/CLionProjects/Shell/Book_2.0/main.cpp -o CMakeFiles/Book_2_0.dir/main.cpp.s

# Object files for target Book_2_0
Book_2_0_OBJECTS = \
"CMakeFiles/Book_2_0.dir/main.cpp.o"

# External object files for target Book_2_0
Book_2_0_EXTERNAL_OBJECTS =

Book_2_0: CMakeFiles/Book_2_0.dir/main.cpp.o
Book_2_0: CMakeFiles/Book_2_0.dir/build.make
Book_2_0: CMakeFiles/Book_2_0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/agavrilenko/CLionProjects/Shell/Book_2.0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Book_2_0"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Book_2_0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Book_2_0.dir/build: Book_2_0

.PHONY : CMakeFiles/Book_2_0.dir/build

CMakeFiles/Book_2_0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Book_2_0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Book_2_0.dir/clean

CMakeFiles/Book_2_0.dir/depend:
	cd /home/agavrilenko/CLionProjects/Shell/Book_2.0/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/agavrilenko/CLionProjects/Shell/Book_2.0 /home/agavrilenko/CLionProjects/Shell/Book_2.0 /home/agavrilenko/CLionProjects/Shell/Book_2.0/cmake-build-debug /home/agavrilenko/CLionProjects/Shell/Book_2.0/cmake-build-debug /home/agavrilenko/CLionProjects/Shell/Book_2.0/cmake-build-debug/CMakeFiles/Book_2_0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Book_2_0.dir/depend

