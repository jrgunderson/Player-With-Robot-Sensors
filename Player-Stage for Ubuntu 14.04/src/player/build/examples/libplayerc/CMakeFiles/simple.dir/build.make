# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jrgunderson/Downloads/player

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jrgunderson/Downloads/player/build

# Include any dependencies generated for this target.
include examples/libplayerc/CMakeFiles/simple.dir/depend.make

# Include the progress variables for this target.
include examples/libplayerc/CMakeFiles/simple.dir/progress.make

# Include the compile flags for this target's objects.
include examples/libplayerc/CMakeFiles/simple.dir/flags.make

examples/libplayerc/CMakeFiles/simple.dir/simple.o: examples/libplayerc/CMakeFiles/simple.dir/flags.make
examples/libplayerc/CMakeFiles/simple.dir/simple.o: ../examples/libplayerc/simple.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jrgunderson/Downloads/player/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/libplayerc/CMakeFiles/simple.dir/simple.o"
	cd /home/jrgunderson/Downloads/player/build/examples/libplayerc && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/simple.dir/simple.o   -c /home/jrgunderson/Downloads/player/examples/libplayerc/simple.c

examples/libplayerc/CMakeFiles/simple.dir/simple.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/simple.dir/simple.i"
	cd /home/jrgunderson/Downloads/player/build/examples/libplayerc && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/jrgunderson/Downloads/player/examples/libplayerc/simple.c > CMakeFiles/simple.dir/simple.i

examples/libplayerc/CMakeFiles/simple.dir/simple.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/simple.dir/simple.s"
	cd /home/jrgunderson/Downloads/player/build/examples/libplayerc && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/jrgunderson/Downloads/player/examples/libplayerc/simple.c -o CMakeFiles/simple.dir/simple.s

examples/libplayerc/CMakeFiles/simple.dir/simple.o.requires:
.PHONY : examples/libplayerc/CMakeFiles/simple.dir/simple.o.requires

examples/libplayerc/CMakeFiles/simple.dir/simple.o.provides: examples/libplayerc/CMakeFiles/simple.dir/simple.o.requires
	$(MAKE) -f examples/libplayerc/CMakeFiles/simple.dir/build.make examples/libplayerc/CMakeFiles/simple.dir/simple.o.provides.build
.PHONY : examples/libplayerc/CMakeFiles/simple.dir/simple.o.provides

examples/libplayerc/CMakeFiles/simple.dir/simple.o.provides.build: examples/libplayerc/CMakeFiles/simple.dir/simple.o

# Object files for target simple
simple_OBJECTS = \
"CMakeFiles/simple.dir/simple.o"

# External object files for target simple
simple_EXTERNAL_OBJECTS =

examples/libplayerc/simple: examples/libplayerc/CMakeFiles/simple.dir/simple.o
examples/libplayerc/simple: examples/libplayerc/CMakeFiles/simple.dir/build.make
examples/libplayerc/simple: client_libs/libplayerc/libplayerc.so.3.1.0-svn
examples/libplayerc/simple: libplayerinterface/libplayerinterface.so.3.1.0-svn
examples/libplayerc/simple: libplayercommon/libplayercommon.so.3.1.0-svn
examples/libplayerc/simple: libplayerwkb/libplayerwkb.so.3.1.0-svn
examples/libplayerc/simple: libplayercommon/libplayercommon.so.3.1.0-svn
examples/libplayerc/simple: libplayerjpeg/libplayerjpeg.so.3.1.0-svn
examples/libplayerc/simple: examples/libplayerc/CMakeFiles/simple.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable simple"
	cd /home/jrgunderson/Downloads/player/build/examples/libplayerc && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simple.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/libplayerc/CMakeFiles/simple.dir/build: examples/libplayerc/simple
.PHONY : examples/libplayerc/CMakeFiles/simple.dir/build

examples/libplayerc/CMakeFiles/simple.dir/requires: examples/libplayerc/CMakeFiles/simple.dir/simple.o.requires
.PHONY : examples/libplayerc/CMakeFiles/simple.dir/requires

examples/libplayerc/CMakeFiles/simple.dir/clean:
	cd /home/jrgunderson/Downloads/player/build/examples/libplayerc && $(CMAKE_COMMAND) -P CMakeFiles/simple.dir/cmake_clean.cmake
.PHONY : examples/libplayerc/CMakeFiles/simple.dir/clean

examples/libplayerc/CMakeFiles/simple.dir/depend:
	cd /home/jrgunderson/Downloads/player/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jrgunderson/Downloads/player /home/jrgunderson/Downloads/player/examples/libplayerc /home/jrgunderson/Downloads/player/build /home/jrgunderson/Downloads/player/build/examples/libplayerc /home/jrgunderson/Downloads/player/build/examples/libplayerc/CMakeFiles/simple.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/libplayerc/CMakeFiles/simple.dir/depend

