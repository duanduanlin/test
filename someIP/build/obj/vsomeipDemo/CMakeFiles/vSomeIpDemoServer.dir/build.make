# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dding3/work/test/test/someIP/project/vsomeIpDemo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dding3/work/test/test/someIP/build/obj/vsomeipDemo

# Include any dependencies generated for this target.
include CMakeFiles/vSomeIpDemoServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vSomeIpDemoServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vSomeIpDemoServer.dir/flags.make

CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.o: CMakeFiles/vSomeIpDemoServer.dir/flags.make
CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.o: /home/dding3/work/test/test/someIP/project/vsomeIpDemo/src/someip_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dding3/work/test/test/someIP/build/obj/vsomeipDemo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.o -c /home/dding3/work/test/test/someIP/project/vsomeIpDemo/src/someip_server.cpp

CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dding3/work/test/test/someIP/project/vsomeIpDemo/src/someip_server.cpp > CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.i

CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dding3/work/test/test/someIP/project/vsomeIpDemo/src/someip_server.cpp -o CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.s

# Object files for target vSomeIpDemoServer
vSomeIpDemoServer_OBJECTS = \
"CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.o"

# External object files for target vSomeIpDemoServer
vSomeIpDemoServer_EXTERNAL_OBJECTS =

/home/dding3/work/test/test/someIP/output/apps/bin/vSomeIpDemoServer: CMakeFiles/vSomeIpDemoServer.dir/src/someip_server.cpp.o
/home/dding3/work/test/test/someIP/output/apps/bin/vSomeIpDemoServer: CMakeFiles/vSomeIpDemoServer.dir/build.make
/home/dding3/work/test/test/someIP/output/apps/bin/vSomeIpDemoServer: /usr/local/lib/libvsomeip3.so.3.3.8
/home/dding3/work/test/test/someIP/output/apps/bin/vSomeIpDemoServer: CMakeFiles/vSomeIpDemoServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dding3/work/test/test/someIP/build/obj/vsomeipDemo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/dding3/work/test/test/someIP/output/apps/bin/vSomeIpDemoServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vSomeIpDemoServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vSomeIpDemoServer.dir/build: /home/dding3/work/test/test/someIP/output/apps/bin/vSomeIpDemoServer

.PHONY : CMakeFiles/vSomeIpDemoServer.dir/build

CMakeFiles/vSomeIpDemoServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vSomeIpDemoServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vSomeIpDemoServer.dir/clean

CMakeFiles/vSomeIpDemoServer.dir/depend:
	cd /home/dding3/work/test/test/someIP/build/obj/vsomeipDemo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dding3/work/test/test/someIP/project/vsomeIpDemo /home/dding3/work/test/test/someIP/project/vsomeIpDemo /home/dding3/work/test/test/someIP/build/obj/vsomeipDemo /home/dding3/work/test/test/someIP/build/obj/vsomeipDemo /home/dding3/work/test/test/someIP/build/obj/vsomeipDemo/CMakeFiles/vSomeIpDemoServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vSomeIpDemoServer.dir/depend

