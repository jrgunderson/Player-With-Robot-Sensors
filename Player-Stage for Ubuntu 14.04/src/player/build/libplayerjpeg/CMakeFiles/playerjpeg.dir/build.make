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
include libplayerjpeg/CMakeFiles/playerjpeg.dir/depend.make

# Include the progress variables for this target.
include libplayerjpeg/CMakeFiles/playerjpeg.dir/progress.make

# Include the compile flags for this target's objects.
include libplayerjpeg/CMakeFiles/playerjpeg.dir/flags.make

libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o: libplayerjpeg/CMakeFiles/playerjpeg.dir/flags.make
libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o: ../libplayerjpeg/playerjpeg.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jrgunderson/Downloads/player/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o"
	cd /home/jrgunderson/Downloads/player/build/libplayerjpeg && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/playerjpeg.dir/playerjpeg.o   -c /home/jrgunderson/Downloads/player/libplayerjpeg/playerjpeg.c

libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/playerjpeg.dir/playerjpeg.i"
	cd /home/jrgunderson/Downloads/player/build/libplayerjpeg && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/jrgunderson/Downloads/player/libplayerjpeg/playerjpeg.c > CMakeFiles/playerjpeg.dir/playerjpeg.i

libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/playerjpeg.dir/playerjpeg.s"
	cd /home/jrgunderson/Downloads/player/build/libplayerjpeg && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/jrgunderson/Downloads/player/libplayerjpeg/playerjpeg.c -o CMakeFiles/playerjpeg.dir/playerjpeg.s

libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o.requires:
.PHONY : libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o.requires

libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o.provides: libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o.requires
	$(MAKE) -f libplayerjpeg/CMakeFiles/playerjpeg.dir/build.make libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o.provides.build
.PHONY : libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o.provides

libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o.provides.build: libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o

# Object files for target playerjpeg
playerjpeg_OBJECTS = \
"CMakeFiles/playerjpeg.dir/playerjpeg.o"

# External object files for target playerjpeg
playerjpeg_EXTERNAL_OBJECTS =

libplayerjpeg/libplayerjpeg.so.3.1.0-svn: libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o
libplayerjpeg/libplayerjpeg.so.3.1.0-svn: libplayerjpeg/CMakeFiles/playerjpeg.dir/build.make
libplayerjpeg/libplayerjpeg.so.3.1.0-svn: libplayerjpeg/CMakeFiles/playerjpeg.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libplayerjpeg.so"
	cd /home/jrgunderson/Downloads/player/build/libplayerjpeg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/playerjpeg.dir/link.txt --verbose=$(VERBOSE)
	cd /home/jrgunderson/Downloads/player/build/libplayerjpeg && $(CMAKE_COMMAND) -E cmake_symlink_library libplayerjpeg.so.3.1.0-svn libplayerjpeg.so.3.1 libplayerjpeg.so

libplayerjpeg/libplayerjpeg.so.3.1: libplayerjpeg/libplayerjpeg.so.3.1.0-svn

libplayerjpeg/libplayerjpeg.so: libplayerjpeg/libplayerjpeg.so.3.1.0-svn

# Rule to build all files generated by this target.
libplayerjpeg/CMakeFiles/playerjpeg.dir/build: libplayerjpeg/libplayerjpeg.so
.PHONY : libplayerjpeg/CMakeFiles/playerjpeg.dir/build

libplayerjpeg/CMakeFiles/playerjpeg.dir/requires: libplayerjpeg/CMakeFiles/playerjpeg.dir/playerjpeg.o.requires
.PHONY : libplayerjpeg/CMakeFiles/playerjpeg.dir/requires

libplayerjpeg/CMakeFiles/playerjpeg.dir/clean:
	cd /home/jrgunderson/Downloads/player/build/libplayerjpeg && $(CMAKE_COMMAND) -P CMakeFiles/playerjpeg.dir/cmake_clean.cmake
.PHONY : libplayerjpeg/CMakeFiles/playerjpeg.dir/clean

libplayerjpeg/CMakeFiles/playerjpeg.dir/depend:
	cd /home/jrgunderson/Downloads/player/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jrgunderson/Downloads/player /home/jrgunderson/Downloads/player/libplayerjpeg /home/jrgunderson/Downloads/player/build /home/jrgunderson/Downloads/player/build/libplayerjpeg /home/jrgunderson/Downloads/player/build/libplayerjpeg/CMakeFiles/playerjpeg.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libplayerjpeg/CMakeFiles/playerjpeg.dir/depend

