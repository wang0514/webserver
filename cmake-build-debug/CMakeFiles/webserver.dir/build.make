# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /home/wangkaikai/Downloads/clion-2019.1.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/wangkaikai/Downloads/clion-2019.1.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/wangkaikai/project/webserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wangkaikai/project/webserver/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/webserver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/webserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/webserver.dir/flags.make

CMakeFiles/webserver.dir/main.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/webserver.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/main.cpp.o -c /home/wangkaikai/project/webserver/main.cpp

CMakeFiles/webserver.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/main.cpp > CMakeFiles/webserver.dir/main.cpp.i

CMakeFiles/webserver.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/main.cpp -o CMakeFiles/webserver.dir/main.cpp.s

CMakeFiles/webserver.dir/EventLoop.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/EventLoop.cpp.o: ../EventLoop.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/webserver.dir/EventLoop.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/EventLoop.cpp.o -c /home/wangkaikai/project/webserver/EventLoop.cpp

CMakeFiles/webserver.dir/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/EventLoop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/EventLoop.cpp > CMakeFiles/webserver.dir/EventLoop.cpp.i

CMakeFiles/webserver.dir/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/EventLoop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/EventLoop.cpp -o CMakeFiles/webserver.dir/EventLoop.cpp.s

CMakeFiles/webserver.dir/Util.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Util.cpp.o: ../Util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/webserver.dir/Util.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Util.cpp.o -c /home/wangkaikai/project/webserver/Util.cpp

CMakeFiles/webserver.dir/Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Util.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/Util.cpp > CMakeFiles/webserver.dir/Util.cpp.i

CMakeFiles/webserver.dir/Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Util.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/Util.cpp -o CMakeFiles/webserver.dir/Util.cpp.s

CMakeFiles/webserver.dir/Epoll.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Epoll.cpp.o: ../Epoll.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/webserver.dir/Epoll.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Epoll.cpp.o -c /home/wangkaikai/project/webserver/Epoll.cpp

CMakeFiles/webserver.dir/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Epoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/Epoll.cpp > CMakeFiles/webserver.dir/Epoll.cpp.i

CMakeFiles/webserver.dir/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Epoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/Epoll.cpp -o CMakeFiles/webserver.dir/Epoll.cpp.s

CMakeFiles/webserver.dir/Channel.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Channel.cpp.o: ../Channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/webserver.dir/Channel.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Channel.cpp.o -c /home/wangkaikai/project/webserver/Channel.cpp

CMakeFiles/webserver.dir/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Channel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/Channel.cpp > CMakeFiles/webserver.dir/Channel.cpp.i

CMakeFiles/webserver.dir/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Channel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/Channel.cpp -o CMakeFiles/webserver.dir/Channel.cpp.s

CMakeFiles/webserver.dir/Thread.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/Thread.cpp.o: ../Thread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/webserver.dir/Thread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/Thread.cpp.o -c /home/wangkaikai/project/webserver/Thread.cpp

CMakeFiles/webserver.dir/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/Thread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/Thread.cpp > CMakeFiles/webserver.dir/Thread.cpp.i

CMakeFiles/webserver.dir/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/Thread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/Thread.cpp -o CMakeFiles/webserver.dir/Thread.cpp.s

CMakeFiles/webserver.dir/CountDownLatch.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/CountDownLatch.cpp.o: ../CountDownLatch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/webserver.dir/CountDownLatch.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/CountDownLatch.cpp.o -c /home/wangkaikai/project/webserver/CountDownLatch.cpp

CMakeFiles/webserver.dir/CountDownLatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/CountDownLatch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/CountDownLatch.cpp > CMakeFiles/webserver.dir/CountDownLatch.cpp.i

CMakeFiles/webserver.dir/CountDownLatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/CountDownLatch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/CountDownLatch.cpp -o CMakeFiles/webserver.dir/CountDownLatch.cpp.s

CMakeFiles/webserver.dir/EventLoopThread.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/EventLoopThread.cpp.o: ../EventLoopThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/webserver.dir/EventLoopThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/EventLoopThread.cpp.o -c /home/wangkaikai/project/webserver/EventLoopThread.cpp

CMakeFiles/webserver.dir/EventLoopThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/EventLoopThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/EventLoopThread.cpp > CMakeFiles/webserver.dir/EventLoopThread.cpp.i

CMakeFiles/webserver.dir/EventLoopThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/EventLoopThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/EventLoopThread.cpp -o CMakeFiles/webserver.dir/EventLoopThread.cpp.s

CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.o: ../EventLoopThreadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.o -c /home/wangkaikai/project/webserver/EventLoopThreadPool.cpp

CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/EventLoopThreadPool.cpp > CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.i

CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/EventLoopThreadPool.cpp -o CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.s

CMakeFiles/webserver.dir/HttpServer.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/HttpServer.cpp.o: ../HttpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/webserver.dir/HttpServer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/HttpServer.cpp.o -c /home/wangkaikai/project/webserver/HttpServer.cpp

CMakeFiles/webserver.dir/HttpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/HttpServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/HttpServer.cpp > CMakeFiles/webserver.dir/HttpServer.cpp.i

CMakeFiles/webserver.dir/HttpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/HttpServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/HttpServer.cpp -o CMakeFiles/webserver.dir/HttpServer.cpp.s

CMakeFiles/webserver.dir/HttpData.cpp.o: CMakeFiles/webserver.dir/flags.make
CMakeFiles/webserver.dir/HttpData.cpp.o: ../HttpData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/webserver.dir/HttpData.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/webserver.dir/HttpData.cpp.o -c /home/wangkaikai/project/webserver/HttpData.cpp

CMakeFiles/webserver.dir/HttpData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/webserver.dir/HttpData.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wangkaikai/project/webserver/HttpData.cpp > CMakeFiles/webserver.dir/HttpData.cpp.i

CMakeFiles/webserver.dir/HttpData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/webserver.dir/HttpData.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wangkaikai/project/webserver/HttpData.cpp -o CMakeFiles/webserver.dir/HttpData.cpp.s

# Object files for target webserver
webserver_OBJECTS = \
"CMakeFiles/webserver.dir/main.cpp.o" \
"CMakeFiles/webserver.dir/EventLoop.cpp.o" \
"CMakeFiles/webserver.dir/Util.cpp.o" \
"CMakeFiles/webserver.dir/Epoll.cpp.o" \
"CMakeFiles/webserver.dir/Channel.cpp.o" \
"CMakeFiles/webserver.dir/Thread.cpp.o" \
"CMakeFiles/webserver.dir/CountDownLatch.cpp.o" \
"CMakeFiles/webserver.dir/EventLoopThread.cpp.o" \
"CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.o" \
"CMakeFiles/webserver.dir/HttpServer.cpp.o" \
"CMakeFiles/webserver.dir/HttpData.cpp.o"

# External object files for target webserver
webserver_EXTERNAL_OBJECTS =

webserver: CMakeFiles/webserver.dir/main.cpp.o
webserver: CMakeFiles/webserver.dir/EventLoop.cpp.o
webserver: CMakeFiles/webserver.dir/Util.cpp.o
webserver: CMakeFiles/webserver.dir/Epoll.cpp.o
webserver: CMakeFiles/webserver.dir/Channel.cpp.o
webserver: CMakeFiles/webserver.dir/Thread.cpp.o
webserver: CMakeFiles/webserver.dir/CountDownLatch.cpp.o
webserver: CMakeFiles/webserver.dir/EventLoopThread.cpp.o
webserver: CMakeFiles/webserver.dir/EventLoopThreadPool.cpp.o
webserver: CMakeFiles/webserver.dir/HttpServer.cpp.o
webserver: CMakeFiles/webserver.dir/HttpData.cpp.o
webserver: CMakeFiles/webserver.dir/build.make
webserver: CMakeFiles/webserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX executable webserver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/webserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/webserver.dir/build: webserver

.PHONY : CMakeFiles/webserver.dir/build

CMakeFiles/webserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/webserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/webserver.dir/clean

CMakeFiles/webserver.dir/depend:
	cd /home/wangkaikai/project/webserver/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wangkaikai/project/webserver /home/wangkaikai/project/webserver /home/wangkaikai/project/webserver/cmake-build-debug /home/wangkaikai/project/webserver/cmake-build-debug /home/wangkaikai/project/webserver/cmake-build-debug/CMakeFiles/webserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/webserver.dir/depend

