# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/miir_ho3ein/projects/pulp/applications/residual_vq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/miir_ho3ein/projects/pulp/applications/residual_vq/build

# Utility rule file for dump_dis.

# Include any custom commands dependencies for this target.
include CMakeFiles/dump_dis.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/dump_dis.dir/progress.make

CMakeFiles/dump_dis: vq_block
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/miir_ho3ein/projects/pulp/applications/residual_vq/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Invoking: OBJDUMP, dump disassembly in /home/miir_ho3ein/projects/pulp/applications/residual_vq/build/vq_block.s"
	/usr/lib/gap_riscv_toolchain/bin/riscv32-unknown-elf-objdump -d -h -S -t -w --show-raw-insn /home/miir_ho3ein/projects/pulp/applications/residual_vq/build/vq_block > /home/miir_ho3ein/projects/pulp/applications/residual_vq/build/vq_block.s

dump_dis: CMakeFiles/dump_dis
dump_dis: CMakeFiles/dump_dis.dir/build.make
.PHONY : dump_dis

# Rule to build all files generated by this target.
CMakeFiles/dump_dis.dir/build: dump_dis
.PHONY : CMakeFiles/dump_dis.dir/build

CMakeFiles/dump_dis.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dump_dis.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dump_dis.dir/clean

CMakeFiles/dump_dis.dir/depend:
	cd /home/miir_ho3ein/projects/pulp/applications/residual_vq/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/miir_ho3ein/projects/pulp/applications/residual_vq /home/miir_ho3ein/projects/pulp/applications/residual_vq /home/miir_ho3ein/projects/pulp/applications/residual_vq/build /home/miir_ho3ein/projects/pulp/applications/residual_vq/build /home/miir_ho3ein/projects/pulp/applications/residual_vq/build/CMakeFiles/dump_dis.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/dump_dis.dir/depend

