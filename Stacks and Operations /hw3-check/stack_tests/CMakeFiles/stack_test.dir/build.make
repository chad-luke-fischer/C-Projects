# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/student/hw-clfische/hw3/hw3-check

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/student/hw-clfische/hw3/hw3-check

# Include any dependencies generated for this target.
include stack_tests/CMakeFiles/stack_test.dir/depend.make

# Include the progress variables for this target.
include stack_tests/CMakeFiles/stack_test.dir/progress.make

# Include the compile flags for this target's objects.
include stack_tests/CMakeFiles/stack_test.dir/flags.make

stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o: stack_tests/CMakeFiles/stack_test.dir/flags.make
stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o: stack_tests/stack_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/hw-clfische/hw3/hw3-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o"
	cd /home/student/hw-clfische/hw3/hw3-check/stack_tests && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stack_test.dir/stack_test.cpp.o -c /home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test.cpp

stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stack_test.dir/stack_test.cpp.i"
	cd /home/student/hw-clfische/hw3/hw3-check/stack_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test.cpp > CMakeFiles/stack_test.dir/stack_test.cpp.i

stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stack_test.dir/stack_test.cpp.s"
	cd /home/student/hw-clfische/hw3/hw3-check/stack_tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test.cpp -o CMakeFiles/stack_test.dir/stack_test.cpp.s

stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o.requires:

.PHONY : stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o.requires

stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o.provides: stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o.requires
	$(MAKE) -f stack_tests/CMakeFiles/stack_test.dir/build.make stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o.provides.build
.PHONY : stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o.provides

stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o.provides.build: stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o


# Object files for target stack_test
stack_test_OBJECTS = \
"CMakeFiles/stack_test.dir/stack_test.cpp.o"

# External object files for target stack_test
stack_test_EXTERNAL_OBJECTS =

stack_tests/stack_test: stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o
stack_tests/stack_test: stack_tests/CMakeFiles/stack_test.dir/build.make
stack_tests/stack_test: testing_utils/libtesting_utils.a
stack_tests/stack_test: /usr/lib/libgtest.a
stack_tests/stack_test: libhw3_user_code.a
stack_tests/stack_test: testing_utils/kwsys/libkwsys.a
stack_tests/stack_test: /usr/lib/libgtest_main.a
stack_tests/stack_test: stack_tests/CMakeFiles/stack_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/student/hw-clfische/hw3/hw3-check/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable stack_test"
	cd /home/student/hw-clfische/hw3/hw3-check/stack_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stack_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
stack_tests/CMakeFiles/stack_test.dir/build: stack_tests/stack_test

.PHONY : stack_tests/CMakeFiles/stack_test.dir/build

stack_tests/CMakeFiles/stack_test.dir/requires: stack_tests/CMakeFiles/stack_test.dir/stack_test.cpp.o.requires

.PHONY : stack_tests/CMakeFiles/stack_test.dir/requires

stack_tests/CMakeFiles/stack_test.dir/clean:
	cd /home/student/hw-clfische/hw3/hw3-check/stack_tests && $(CMAKE_COMMAND) -P CMakeFiles/stack_test.dir/cmake_clean.cmake
.PHONY : stack_tests/CMakeFiles/stack_test.dir/clean

stack_tests/CMakeFiles/stack_test.dir/depend:
	cd /home/student/hw-clfische/hw3/hw3-check && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/student/hw-clfische/hw3/hw3-check /home/student/hw-clfische/hw3/hw3-check/stack_tests /home/student/hw-clfische/hw3/hw3-check /home/student/hw-clfische/hw3/hw3-check/stack_tests /home/student/hw-clfische/hw3/hw3-check/stack_tests/CMakeFiles/stack_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : stack_tests/CMakeFiles/stack_test.dir/depend

