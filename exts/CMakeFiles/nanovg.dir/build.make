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
CMAKE_SOURCE_DIR = /home/mark/Documents/opengl-lab-env

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/Documents/opengl-lab-env

# Include any dependencies generated for this target.
include exts/CMakeFiles/nanovg.dir/depend.make

# Include the progress variables for this target.
include exts/CMakeFiles/nanovg.dir/progress.make

# Include the compile flags for this target's objects.
include exts/CMakeFiles/nanovg.dir/flags.make

exts/CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.o: exts/CMakeFiles/nanovg.dir/flags.make
exts/CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.o: exts/nanovg/src/nanovg.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Documents/opengl-lab-env/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object exts/CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.o"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.o   -c /home/mark/Documents/opengl-lab-env/exts/nanovg/src/nanovg.c

exts/CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.i"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mark/Documents/opengl-lab-env/exts/nanovg/src/nanovg.c > CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.i

exts/CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.s"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mark/Documents/opengl-lab-env/exts/nanovg/src/nanovg.c -o CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.s

# Object files for target nanovg
nanovg_OBJECTS = \
"CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.o"

# External object files for target nanovg
nanovg_EXTERNAL_OBJECTS =

exts/libnanovg.a: exts/CMakeFiles/nanovg.dir/nanovg/src/nanovg.c.o
exts/libnanovg.a: exts/CMakeFiles/nanovg.dir/build.make
exts/libnanovg.a: exts/CMakeFiles/nanovg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/Documents/opengl-lab-env/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libnanovg.a"
	cd /home/mark/Documents/opengl-lab-env/exts && $(CMAKE_COMMAND) -P CMakeFiles/nanovg.dir/cmake_clean_target.cmake
	cd /home/mark/Documents/opengl-lab-env/exts && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nanovg.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
exts/CMakeFiles/nanovg.dir/build: exts/libnanovg.a

.PHONY : exts/CMakeFiles/nanovg.dir/build

exts/CMakeFiles/nanovg.dir/clean:
	cd /home/mark/Documents/opengl-lab-env/exts && $(CMAKE_COMMAND) -P CMakeFiles/nanovg.dir/cmake_clean.cmake
.PHONY : exts/CMakeFiles/nanovg.dir/clean

exts/CMakeFiles/nanovg.dir/depend:
	cd /home/mark/Documents/opengl-lab-env && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/Documents/opengl-lab-env /home/mark/Documents/opengl-lab-env/exts /home/mark/Documents/opengl-lab-env /home/mark/Documents/opengl-lab-env/exts /home/mark/Documents/opengl-lab-env/exts/CMakeFiles/nanovg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : exts/CMakeFiles/nanovg.dir/depend

