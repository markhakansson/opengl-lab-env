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
include exts/CMakeFiles/imgui.dir/depend.make

# Include the progress variables for this target.
include exts/CMakeFiles/imgui.dir/progress.make

# Include the compile flags for this target's objects.
include exts/CMakeFiles/imgui.dir/flags.make

exts/CMakeFiles/imgui.dir/imgui/imgui.cpp.o: exts/CMakeFiles/imgui.dir/flags.make
exts/CMakeFiles/imgui.dir/imgui/imgui.cpp.o: exts/imgui/imgui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Documents/opengl-lab-env/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object exts/CMakeFiles/imgui.dir/imgui/imgui.cpp.o"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui/imgui.cpp.o -c /home/mark/Documents/opengl-lab-env/exts/imgui/imgui.cpp

exts/CMakeFiles/imgui.dir/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui.cpp.i"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/Documents/opengl-lab-env/exts/imgui/imgui.cpp > CMakeFiles/imgui.dir/imgui/imgui.cpp.i

exts/CMakeFiles/imgui.dir/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui.cpp.s"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/Documents/opengl-lab-env/exts/imgui/imgui.cpp -o CMakeFiles/imgui.dir/imgui/imgui.cpp.s

exts/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o: exts/CMakeFiles/imgui.dir/flags.make
exts/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o: exts/imgui/imgui_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Documents/opengl-lab-env/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object exts/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o -c /home/mark/Documents/opengl-lab-env/exts/imgui/imgui_demo.cpp

exts/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.i"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/Documents/opengl-lab-env/exts/imgui/imgui_demo.cpp > CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.i

exts/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.s"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/Documents/opengl-lab-env/exts/imgui/imgui_demo.cpp -o CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.s

exts/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o: exts/CMakeFiles/imgui.dir/flags.make
exts/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o: exts/imgui/imgui_draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Documents/opengl-lab-env/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object exts/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o -c /home/mark/Documents/opengl-lab-env/exts/imgui/imgui_draw.cpp

exts/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.i"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/Documents/opengl-lab-env/exts/imgui/imgui_draw.cpp > CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.i

exts/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.s"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/Documents/opengl-lab-env/exts/imgui/imgui_draw.cpp -o CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.s

exts/CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.o: exts/CMakeFiles/imgui.dir/flags.make
exts/CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.o: exts/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/Documents/opengl-lab-env/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object exts/CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.o"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.o -c /home/mark/Documents/opengl-lab-env/exts/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp

exts/CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.i"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/Documents/opengl-lab-env/exts/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp > CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.i

exts/CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.s"
	cd /home/mark/Documents/opengl-lab-env/exts && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/Documents/opengl-lab-env/exts/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp -o CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.s

# Object files for target imgui
imgui_OBJECTS = \
"CMakeFiles/imgui.dir/imgui/imgui.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o" \
"CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o" \
"CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.o"

# External object files for target imgui
imgui_EXTERNAL_OBJECTS =

exts/libimgui.a: exts/CMakeFiles/imgui.dir/imgui/imgui.cpp.o
exts/libimgui.a: exts/CMakeFiles/imgui.dir/imgui/imgui_demo.cpp.o
exts/libimgui.a: exts/CMakeFiles/imgui.dir/imgui/imgui_draw.cpp.o
exts/libimgui.a: exts/CMakeFiles/imgui.dir/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp.o
exts/libimgui.a: exts/CMakeFiles/imgui.dir/build.make
exts/libimgui.a: exts/CMakeFiles/imgui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/Documents/opengl-lab-env/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libimgui.a"
	cd /home/mark/Documents/opengl-lab-env/exts && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean_target.cmake
	cd /home/mark/Documents/opengl-lab-env/exts && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
exts/CMakeFiles/imgui.dir/build: exts/libimgui.a

.PHONY : exts/CMakeFiles/imgui.dir/build

exts/CMakeFiles/imgui.dir/clean:
	cd /home/mark/Documents/opengl-lab-env/exts && $(CMAKE_COMMAND) -P CMakeFiles/imgui.dir/cmake_clean.cmake
.PHONY : exts/CMakeFiles/imgui.dir/clean

exts/CMakeFiles/imgui.dir/depend:
	cd /home/mark/Documents/opengl-lab-env && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/Documents/opengl-lab-env /home/mark/Documents/opengl-lab-env/exts /home/mark/Documents/opengl-lab-env /home/mark/Documents/opengl-lab-env/exts /home/mark/Documents/opengl-lab-env/exts/CMakeFiles/imgui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : exts/CMakeFiles/imgui.dir/depend

