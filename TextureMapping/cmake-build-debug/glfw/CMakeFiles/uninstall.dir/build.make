# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/TextureMapping

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/TextureMapping/cmake-build-debug

# Utility rule file for uninstall.

# Include the progress variables for this target.
include glfw/CMakeFiles/uninstall.dir/progress.make

glfw/CMakeFiles/uninstall:
	cd /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/TextureMapping/cmake-build-debug/glfw && /usr/local/Cellar/cmake/3.19.4/bin/cmake -P /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/TextureMapping/cmake-build-debug/glfw/cmake_uninstall.cmake

uninstall: glfw/CMakeFiles/uninstall
uninstall: glfw/CMakeFiles/uninstall.dir/build.make

.PHONY : uninstall

# Rule to build all files generated by this target.
glfw/CMakeFiles/uninstall.dir/build: uninstall

.PHONY : glfw/CMakeFiles/uninstall.dir/build

glfw/CMakeFiles/uninstall.dir/clean:
	cd /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/TextureMapping/cmake-build-debug/glfw && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : glfw/CMakeFiles/uninstall.dir/clean

glfw/CMakeFiles/uninstall.dir/depend:
	cd /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/TextureMapping/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/TextureMapping /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/ext/glfw /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/TextureMapping/cmake-build-debug /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/TextureMapping/cmake-build-debug/glfw /Users/yexu/Documents/GitHub/assignment-3-3d-scene-editor-yalexublue/TextureMapping/cmake-build-debug/glfw/CMakeFiles/uninstall.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : glfw/CMakeFiles/uninstall.dir/depend
