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
include libplayerutil/CMakeFiles/playerutil.dir/depend.make

# Include the progress variables for this target.
include libplayerutil/CMakeFiles/playerutil.dir/progress.make

# Include the compile flags for this target's objects.
include libplayerutil/CMakeFiles/playerutil.dir/flags.make

libplayerutil/CMakeFiles/playerutil.dir/localization.o: libplayerutil/CMakeFiles/playerutil.dir/flags.make
libplayerutil/CMakeFiles/playerutil.dir/localization.o: ../libplayerutil/localization.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/jrgunderson/Downloads/player/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object libplayerutil/CMakeFiles/playerutil.dir/localization.o"
	cd /home/jrgunderson/Downloads/player/build/libplayerutil && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/playerutil.dir/localization.o   -c /home/jrgunderson/Downloads/player/libplayerutil/localization.c

libplayerutil/CMakeFiles/playerutil.dir/localization.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/playerutil.dir/localization.i"
	cd /home/jrgunderson/Downloads/player/build/libplayerutil && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/jrgunderson/Downloads/player/libplayerutil/localization.c > CMakeFiles/playerutil.dir/localization.i

libplayerutil/CMakeFiles/playerutil.dir/localization.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/playerutil.dir/localization.s"
	cd /home/jrgunderson/Downloads/player/build/libplayerutil && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/jrgunderson/Downloads/player/libplayerutil/localization.c -o CMakeFiles/playerutil.dir/localization.s

libplayerutil/CMakeFiles/playerutil.dir/localization.o.requires:
.PHONY : libplayerutil/CMakeFiles/playerutil.dir/localization.o.requires

libplayerutil/CMakeFiles/playerutil.dir/localization.o.provides: libplayerutil/CMakeFiles/playerutil.dir/localization.o.requires
	$(MAKE) -f libplayerutil/CMakeFiles/playerutil.dir/build.make libplayerutil/CMakeFiles/playerutil.dir/localization.o.provides.build
.PHONY : libplayerutil/CMakeFiles/playerutil.dir/localization.o.provides

libplayerutil/CMakeFiles/playerutil.dir/localization.o.provides.build: libplayerutil/CMakeFiles/playerutil.dir/localization.o

# Object files for target playerutil
playerutil_OBJECTS = \
"CMakeFiles/playerutil.dir/localization.o"

# External object files for target playerutil
playerutil_EXTERNAL_OBJECTS =

libplayerutil/libplayerutil.so.3.1.0-svn: libplayerutil/CMakeFiles/playerutil.dir/localization.o
libplayerutil/libplayerutil.so.3.1.0-svn: libplayerutil/CMakeFiles/playerutil.dir/build.make
libplayerutil/libplayerutil.so.3.1.0-svn: libplayerutil/CMakeFiles/playerutil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C shared library libplayerutil.so"
	cd /home/jrgunderson/Downloads/player/build/libplayerutil && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/playerutil.dir/link.txt --verbose=$(VERBOSE)
	cd /home/jrgunderson/Downloads/player/build/libplayerutil && $(CMAKE_COMMAND) -E cmake_symlink_library libplayerutil.so.3.1.0-svn libplayerutil.so.3.1 libplayerutil.so

libplayerutil/libplayerutil.so.3.1: libplayerutil/libplayerutil.so.3.1.0-svn

libplayerutil/libplayerutil.so: libplayerutil/libplayerutil.so.3.1.0-svn

# Rule to build all files generated by this target.
libplayerutil/CMakeFiles/playerutil.dir/build: libplayerutil/libplayerutil.so
.PHONY : libplayerutil/CMakeFiles/playerutil.dir/build

libplayerutil/CMakeFiles/playerutil.dir/requires: libplayerutil/CMakeFiles/playerutil.dir/localization.o.requires
.PHONY : libplayerutil/CMakeFiles/playerutil.dir/requires

libplayerutil/CMakeFiles/playerutil.dir/clean:
	cd /home/jrgunderson/Downloads/player/build/libplayerutil && $(CMAKE_COMMAND) -P CMakeFiles/playerutil.dir/cmake_clean.cmake
.PHONY : libplayerutil/CMakeFiles/playerutil.dir/clean

libplayerutil/CMakeFiles/playerutil.dir/depend:
	cd /home/jrgunderson/Downloads/player/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jrgunderson/Downloads/player /home/jrgunderson/Downloads/player/libplayerutil /home/jrgunderson/Downloads/player/build /home/jrgunderson/Downloads/player/build/libplayerutil /home/jrgunderson/Downloads/player/build/libplayerutil/CMakeFiles/playerutil.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libplayerutil/CMakeFiles/playerutil.dir/depend

