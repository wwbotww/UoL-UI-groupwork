# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /Users/young/anaconda3/envs/UItest-env/bin/cmake

# The command to remove a file.
RM = /Users/young/anaconda3/envs/UItest-env/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/young/Desktop/UoL-UI-groupwork

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/young/Desktop/UoL-UI-groupwork/build

# Utility rule file for water_quality_tool_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/water_quality_tool_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/water_quality_tool_autogen.dir/progress.make

CMakeFiles/water_quality_tool_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/young/Desktop/UoL-UI-groupwork/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target water_quality_tool"
	/Users/young/anaconda3/envs/UItest-env/bin/cmake -E cmake_autogen /Users/young/Desktop/UoL-UI-groupwork/build/CMakeFiles/water_quality_tool_autogen.dir/AutogenInfo.json ""

water_quality_tool_autogen: CMakeFiles/water_quality_tool_autogen
water_quality_tool_autogen: CMakeFiles/water_quality_tool_autogen.dir/build.make
.PHONY : water_quality_tool_autogen

# Rule to build all files generated by this target.
CMakeFiles/water_quality_tool_autogen.dir/build: water_quality_tool_autogen
.PHONY : CMakeFiles/water_quality_tool_autogen.dir/build

CMakeFiles/water_quality_tool_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/water_quality_tool_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/water_quality_tool_autogen.dir/clean

CMakeFiles/water_quality_tool_autogen.dir/depend:
	cd /Users/young/Desktop/UoL-UI-groupwork/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/young/Desktop/UoL-UI-groupwork /Users/young/Desktop/UoL-UI-groupwork /Users/young/Desktop/UoL-UI-groupwork/build /Users/young/Desktop/UoL-UI-groupwork/build /Users/young/Desktop/UoL-UI-groupwork/build/CMakeFiles/water_quality_tool_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/water_quality_tool_autogen.dir/depend

