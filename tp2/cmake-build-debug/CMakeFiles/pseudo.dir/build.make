# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/137/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/137/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/armand/Documents/Advanced Algorithmics/tp2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/armand/Documents/Advanced Algorithmics/tp2/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/pseudo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pseudo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pseudo.dir/flags.make

CMakeFiles/pseudo.dir/pseudo.c.o: CMakeFiles/pseudo.dir/flags.make
CMakeFiles/pseudo.dir/pseudo.c.o: ../pseudo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/armand/Documents/Advanced Algorithmics/tp2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/pseudo.dir/pseudo.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/pseudo.dir/pseudo.c.o   -c "/home/armand/Documents/Advanced Algorithmics/tp2/pseudo.c"

CMakeFiles/pseudo.dir/pseudo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pseudo.dir/pseudo.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/armand/Documents/Advanced Algorithmics/tp2/pseudo.c" > CMakeFiles/pseudo.dir/pseudo.c.i

CMakeFiles/pseudo.dir/pseudo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pseudo.dir/pseudo.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/armand/Documents/Advanced Algorithmics/tp2/pseudo.c" -o CMakeFiles/pseudo.dir/pseudo.c.s

# Object files for target pseudo
pseudo_OBJECTS = \
"CMakeFiles/pseudo.dir/pseudo.c.o"

# External object files for target pseudo
pseudo_EXTERNAL_OBJECTS =

pseudo: CMakeFiles/pseudo.dir/pseudo.c.o
pseudo: CMakeFiles/pseudo.dir/build.make
pseudo: CMakeFiles/pseudo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/armand/Documents/Advanced Algorithmics/tp2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable pseudo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pseudo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pseudo.dir/build: pseudo

.PHONY : CMakeFiles/pseudo.dir/build

CMakeFiles/pseudo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pseudo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pseudo.dir/clean

CMakeFiles/pseudo.dir/depend:
	cd "/home/armand/Documents/Advanced Algorithmics/tp2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/armand/Documents/Advanced Algorithmics/tp2" "/home/armand/Documents/Advanced Algorithmics/tp2" "/home/armand/Documents/Advanced Algorithmics/tp2/cmake-build-debug" "/home/armand/Documents/Advanced Algorithmics/tp2/cmake-build-debug" "/home/armand/Documents/Advanced Algorithmics/tp2/cmake-build-debug/CMakeFiles/pseudo.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/pseudo.dir/depend

