# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\LocalFiles\Programs\Clion\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\LocalFiles\Programs\Clion\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\LocalFiles\Robotics\Projects\SkylineFRCTemplate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\LocalFiles\Robotics\Projects\SkylineFRCTemplate\cmake-build-debug

# Utility rule file for frcUserProgram_debug_deploy.

# Include the progress variables for this target.
include CMakeFiles/frcUserProgram_debug_deploy.dir/progress.make

CMakeFiles/frcUserProgram_debug_deploy:
	cd /d C:\LocalFiles\Robotics\Projects\SkylineFRCTemplate && call gradlew.bat deploy

frcUserProgram_debug_deploy: CMakeFiles/frcUserProgram_debug_deploy
frcUserProgram_debug_deploy: CMakeFiles/frcUserProgram_debug_deploy.dir/build.make

.PHONY : frcUserProgram_debug_deploy

# Rule to build all files generated by this target.
CMakeFiles/frcUserProgram_debug_deploy.dir/build: frcUserProgram_debug_deploy

.PHONY : CMakeFiles/frcUserProgram_debug_deploy.dir/build

CMakeFiles/frcUserProgram_debug_deploy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\frcUserProgram_debug_deploy.dir\cmake_clean.cmake
.PHONY : CMakeFiles/frcUserProgram_debug_deploy.dir/clean

CMakeFiles/frcUserProgram_debug_deploy.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\LocalFiles\Robotics\Projects\SkylineFRCTemplate C:\LocalFiles\Robotics\Projects\SkylineFRCTemplate C:\LocalFiles\Robotics\Projects\SkylineFRCTemplate\cmake-build-debug C:\LocalFiles\Robotics\Projects\SkylineFRCTemplate\cmake-build-debug C:\LocalFiles\Robotics\Projects\SkylineFRCTemplate\cmake-build-debug\CMakeFiles\frcUserProgram_debug_deploy.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/frcUserProgram_debug_deploy.dir/depend

