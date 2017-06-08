# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:
.PHONY : .NOTPARALLEL

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
CMAKE_SOURCE_DIR = /home/remy/git/AutonomousRobot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/remy/git/AutonomousRobot

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/remy/git/AutonomousRobot/CMakeFiles /home/remy/git/AutonomousRobot/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/remy/git/AutonomousRobot/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named comparison

# Build rule for target.
comparison: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 comparison
.PHONY : comparison

# fast build rule for target.
comparison/fast:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/build
.PHONY : comparison/fast

#=============================================================================
# Target rules for targets named datas

# Build rule for target.
datas: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 datas
.PHONY : datas

# fast build rule for target.
datas/fast:
	$(MAKE) -f CMakeFiles/datas.dir/build.make CMakeFiles/datas.dir/build
.PHONY : datas/fast

#=============================================================================
# Target rules for targets named serial

# Build rule for target.
serial: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 serial
.PHONY : serial

# fast build rule for target.
serial/fast:
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/build
.PHONY : serial/fast

src/rasp/imageProcessing/imageUtility.o: src/rasp/imageProcessing/imageUtility.c.o
.PHONY : src/rasp/imageProcessing/imageUtility.o

# target to build an object file
src/rasp/imageProcessing/imageUtility.c.o:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/src/rasp/imageProcessing/imageUtility.c.o
	$(MAKE) -f CMakeFiles/datas.dir/build.make CMakeFiles/datas.dir/src/rasp/imageProcessing/imageUtility.c.o
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/src/rasp/imageProcessing/imageUtility.c.o
.PHONY : src/rasp/imageProcessing/imageUtility.c.o

src/rasp/imageProcessing/imageUtility.i: src/rasp/imageProcessing/imageUtility.c.i
.PHONY : src/rasp/imageProcessing/imageUtility.i

# target to preprocess a source file
src/rasp/imageProcessing/imageUtility.c.i:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/src/rasp/imageProcessing/imageUtility.c.i
	$(MAKE) -f CMakeFiles/datas.dir/build.make CMakeFiles/datas.dir/src/rasp/imageProcessing/imageUtility.c.i
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/src/rasp/imageProcessing/imageUtility.c.i
.PHONY : src/rasp/imageProcessing/imageUtility.c.i

src/rasp/imageProcessing/imageUtility.s: src/rasp/imageProcessing/imageUtility.c.s
.PHONY : src/rasp/imageProcessing/imageUtility.s

# target to generate assembly for a file
src/rasp/imageProcessing/imageUtility.c.s:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/src/rasp/imageProcessing/imageUtility.c.s
	$(MAKE) -f CMakeFiles/datas.dir/build.make CMakeFiles/datas.dir/src/rasp/imageProcessing/imageUtility.c.s
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/src/rasp/imageProcessing/imageUtility.c.s
.PHONY : src/rasp/imageProcessing/imageUtility.c.s

src/rasp/imageProcessing/saveLoad.o: src/rasp/imageProcessing/saveLoad.c.o
.PHONY : src/rasp/imageProcessing/saveLoad.o

# target to build an object file
src/rasp/imageProcessing/saveLoad.c.o:
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/src/rasp/imageProcessing/saveLoad.c.o
.PHONY : src/rasp/imageProcessing/saveLoad.c.o

src/rasp/imageProcessing/saveLoad.i: src/rasp/imageProcessing/saveLoad.c.i
.PHONY : src/rasp/imageProcessing/saveLoad.i

# target to preprocess a source file
src/rasp/imageProcessing/saveLoad.c.i:
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/src/rasp/imageProcessing/saveLoad.c.i
.PHONY : src/rasp/imageProcessing/saveLoad.c.i

src/rasp/imageProcessing/saveLoad.s: src/rasp/imageProcessing/saveLoad.c.s
.PHONY : src/rasp/imageProcessing/saveLoad.s

# target to generate assembly for a file
src/rasp/imageProcessing/saveLoad.c.s:
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/src/rasp/imageProcessing/saveLoad.c.s
.PHONY : src/rasp/imageProcessing/saveLoad.c.s

src/rasp/main.o: src/rasp/main.c.o
.PHONY : src/rasp/main.o

# target to build an object file
src/rasp/main.c.o:
	$(MAKE) -f CMakeFiles/datas.dir/build.make CMakeFiles/datas.dir/src/rasp/main.c.o
.PHONY : src/rasp/main.c.o

src/rasp/main.i: src/rasp/main.c.i
.PHONY : src/rasp/main.i

# target to preprocess a source file
src/rasp/main.c.i:
	$(MAKE) -f CMakeFiles/datas.dir/build.make CMakeFiles/datas.dir/src/rasp/main.c.i
.PHONY : src/rasp/main.c.i

src/rasp/main.s: src/rasp/main.c.s
.PHONY : src/rasp/main.s

# target to generate assembly for a file
src/rasp/main.c.s:
	$(MAKE) -f CMakeFiles/datas.dir/build.make CMakeFiles/datas.dir/src/rasp/main.c.s
.PHONY : src/rasp/main.c.s

src/rasp/recognition/recognition.o: src/rasp/recognition/recognition.c.o
.PHONY : src/rasp/recognition/recognition.o

# target to build an object file
src/rasp/recognition/recognition.c.o:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/src/rasp/recognition/recognition.c.o
.PHONY : src/rasp/recognition/recognition.c.o

src/rasp/recognition/recognition.i: src/rasp/recognition/recognition.c.i
.PHONY : src/rasp/recognition/recognition.i

# target to preprocess a source file
src/rasp/recognition/recognition.c.i:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/src/rasp/recognition/recognition.c.i
.PHONY : src/rasp/recognition/recognition.c.i

src/rasp/recognition/recognition.s: src/rasp/recognition/recognition.c.s
.PHONY : src/rasp/recognition/recognition.s

# target to generate assembly for a file
src/rasp/recognition/recognition.c.s:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/src/rasp/recognition/recognition.c.s
.PHONY : src/rasp/recognition/recognition.c.s

src/serial/Serial.o: src/serial/Serial.c.o
.PHONY : src/serial/Serial.o

# target to build an object file
src/serial/Serial.c.o:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/src/serial/Serial.c.o
	$(MAKE) -f CMakeFiles/datas.dir/build.make CMakeFiles/datas.dir/src/serial/Serial.c.o
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/src/serial/Serial.c.o
.PHONY : src/serial/Serial.c.o

src/serial/Serial.i: src/serial/Serial.c.i
.PHONY : src/serial/Serial.i

# target to preprocess a source file
src/serial/Serial.c.i:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/src/serial/Serial.c.i
	$(MAKE) -f CMakeFiles/datas.dir/build.make CMakeFiles/datas.dir/src/serial/Serial.c.i
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/src/serial/Serial.c.i
.PHONY : src/serial/Serial.c.i

src/serial/Serial.s: src/serial/Serial.c.s
.PHONY : src/serial/Serial.s

# target to generate assembly for a file
src/serial/Serial.c.s:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/src/serial/Serial.c.s
	$(MAKE) -f CMakeFiles/datas.dir/build.make CMakeFiles/datas.dir/src/serial/Serial.c.s
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/src/serial/Serial.c.s
.PHONY : src/serial/Serial.c.s

tests/comparison.o: tests/comparison.c.o
.PHONY : tests/comparison.o

# target to build an object file
tests/comparison.c.o:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/tests/comparison.c.o
.PHONY : tests/comparison.c.o

tests/comparison.i: tests/comparison.c.i
.PHONY : tests/comparison.i

# target to preprocess a source file
tests/comparison.c.i:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/tests/comparison.c.i
.PHONY : tests/comparison.c.i

tests/comparison.s: tests/comparison.c.s
.PHONY : tests/comparison.s

# target to generate assembly for a file
tests/comparison.c.s:
	$(MAKE) -f CMakeFiles/comparison.dir/build.make CMakeFiles/comparison.dir/tests/comparison.c.s
.PHONY : tests/comparison.c.s

tests/serialTest.o: tests/serialTest.c.o
.PHONY : tests/serialTest.o

# target to build an object file
tests/serialTest.c.o:
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/tests/serialTest.c.o
.PHONY : tests/serialTest.c.o

tests/serialTest.i: tests/serialTest.c.i
.PHONY : tests/serialTest.i

# target to preprocess a source file
tests/serialTest.c.i:
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/tests/serialTest.c.i
.PHONY : tests/serialTest.c.i

tests/serialTest.s: tests/serialTest.c.s
.PHONY : tests/serialTest.s

# target to generate assembly for a file
tests/serialTest.c.s:
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/tests/serialTest.c.s
.PHONY : tests/serialTest.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... comparison"
	@echo "... datas"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... serial"
	@echo "... src/rasp/imageProcessing/imageUtility.o"
	@echo "... src/rasp/imageProcessing/imageUtility.i"
	@echo "... src/rasp/imageProcessing/imageUtility.s"
	@echo "... src/rasp/imageProcessing/saveLoad.o"
	@echo "... src/rasp/imageProcessing/saveLoad.i"
	@echo "... src/rasp/imageProcessing/saveLoad.s"
	@echo "... src/rasp/main.o"
	@echo "... src/rasp/main.i"
	@echo "... src/rasp/main.s"
	@echo "... src/rasp/recognition/recognition.o"
	@echo "... src/rasp/recognition/recognition.i"
	@echo "... src/rasp/recognition/recognition.s"
	@echo "... src/serial/Serial.o"
	@echo "... src/serial/Serial.i"
	@echo "... src/serial/Serial.s"
	@echo "... tests/comparison.o"
	@echo "... tests/comparison.i"
	@echo "... tests/comparison.s"
	@echo "... tests/serialTest.o"
	@echo "... tests/serialTest.i"
	@echo "... tests/serialTest.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

