# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/cmake-3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stu/muduoz

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stu/muduoz/build

# Include any dependencies generated for this target.
include CMakeFiles/mymuduo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mymuduo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mymuduo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mymuduo.dir/flags.make

CMakeFiles/mymuduo.dir/Acceptor.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Acceptor.cc.o: /home/stu/muduoz/Acceptor.cc
CMakeFiles/mymuduo.dir/Acceptor.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mymuduo.dir/Acceptor.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Acceptor.cc.o -MF CMakeFiles/mymuduo.dir/Acceptor.cc.o.d -o CMakeFiles/mymuduo.dir/Acceptor.cc.o -c /home/stu/muduoz/Acceptor.cc

CMakeFiles/mymuduo.dir/Acceptor.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Acceptor.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/Acceptor.cc > CMakeFiles/mymuduo.dir/Acceptor.cc.i

CMakeFiles/mymuduo.dir/Acceptor.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Acceptor.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/Acceptor.cc -o CMakeFiles/mymuduo.dir/Acceptor.cc.s

CMakeFiles/mymuduo.dir/Buffer.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Buffer.cc.o: /home/stu/muduoz/Buffer.cc
CMakeFiles/mymuduo.dir/Buffer.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mymuduo.dir/Buffer.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Buffer.cc.o -MF CMakeFiles/mymuduo.dir/Buffer.cc.o.d -o CMakeFiles/mymuduo.dir/Buffer.cc.o -c /home/stu/muduoz/Buffer.cc

CMakeFiles/mymuduo.dir/Buffer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Buffer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/Buffer.cc > CMakeFiles/mymuduo.dir/Buffer.cc.i

CMakeFiles/mymuduo.dir/Buffer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Buffer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/Buffer.cc -o CMakeFiles/mymuduo.dir/Buffer.cc.s

CMakeFiles/mymuduo.dir/Channel.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Channel.cc.o: /home/stu/muduoz/Channel.cc
CMakeFiles/mymuduo.dir/Channel.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mymuduo.dir/Channel.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Channel.cc.o -MF CMakeFiles/mymuduo.dir/Channel.cc.o.d -o CMakeFiles/mymuduo.dir/Channel.cc.o -c /home/stu/muduoz/Channel.cc

CMakeFiles/mymuduo.dir/Channel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Channel.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/Channel.cc > CMakeFiles/mymuduo.dir/Channel.cc.i

CMakeFiles/mymuduo.dir/Channel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Channel.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/Channel.cc -o CMakeFiles/mymuduo.dir/Channel.cc.s

CMakeFiles/mymuduo.dir/CurrentThread.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/CurrentThread.cc.o: /home/stu/muduoz/CurrentThread.cc
CMakeFiles/mymuduo.dir/CurrentThread.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mymuduo.dir/CurrentThread.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/CurrentThread.cc.o -MF CMakeFiles/mymuduo.dir/CurrentThread.cc.o.d -o CMakeFiles/mymuduo.dir/CurrentThread.cc.o -c /home/stu/muduoz/CurrentThread.cc

CMakeFiles/mymuduo.dir/CurrentThread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/CurrentThread.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/CurrentThread.cc > CMakeFiles/mymuduo.dir/CurrentThread.cc.i

CMakeFiles/mymuduo.dir/CurrentThread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/CurrentThread.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/CurrentThread.cc -o CMakeFiles/mymuduo.dir/CurrentThread.cc.s

CMakeFiles/mymuduo.dir/DefaultPoller.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/DefaultPoller.cc.o: /home/stu/muduoz/DefaultPoller.cc
CMakeFiles/mymuduo.dir/DefaultPoller.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mymuduo.dir/DefaultPoller.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/DefaultPoller.cc.o -MF CMakeFiles/mymuduo.dir/DefaultPoller.cc.o.d -o CMakeFiles/mymuduo.dir/DefaultPoller.cc.o -c /home/stu/muduoz/DefaultPoller.cc

CMakeFiles/mymuduo.dir/DefaultPoller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/DefaultPoller.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/DefaultPoller.cc > CMakeFiles/mymuduo.dir/DefaultPoller.cc.i

CMakeFiles/mymuduo.dir/DefaultPoller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/DefaultPoller.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/DefaultPoller.cc -o CMakeFiles/mymuduo.dir/DefaultPoller.cc.s

CMakeFiles/mymuduo.dir/EPollPoller.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/EPollPoller.cc.o: /home/stu/muduoz/EPollPoller.cc
CMakeFiles/mymuduo.dir/EPollPoller.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/mymuduo.dir/EPollPoller.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/EPollPoller.cc.o -MF CMakeFiles/mymuduo.dir/EPollPoller.cc.o.d -o CMakeFiles/mymuduo.dir/EPollPoller.cc.o -c /home/stu/muduoz/EPollPoller.cc

CMakeFiles/mymuduo.dir/EPollPoller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/EPollPoller.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/EPollPoller.cc > CMakeFiles/mymuduo.dir/EPollPoller.cc.i

CMakeFiles/mymuduo.dir/EPollPoller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/EPollPoller.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/EPollPoller.cc -o CMakeFiles/mymuduo.dir/EPollPoller.cc.s

CMakeFiles/mymuduo.dir/EventLoop.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/EventLoop.cc.o: /home/stu/muduoz/EventLoop.cc
CMakeFiles/mymuduo.dir/EventLoop.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/mymuduo.dir/EventLoop.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/EventLoop.cc.o -MF CMakeFiles/mymuduo.dir/EventLoop.cc.o.d -o CMakeFiles/mymuduo.dir/EventLoop.cc.o -c /home/stu/muduoz/EventLoop.cc

CMakeFiles/mymuduo.dir/EventLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/EventLoop.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/EventLoop.cc > CMakeFiles/mymuduo.dir/EventLoop.cc.i

CMakeFiles/mymuduo.dir/EventLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/EventLoop.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/EventLoop.cc -o CMakeFiles/mymuduo.dir/EventLoop.cc.s

CMakeFiles/mymuduo.dir/EventLoopThread.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/EventLoopThread.cc.o: /home/stu/muduoz/EventLoopThread.cc
CMakeFiles/mymuduo.dir/EventLoopThread.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/mymuduo.dir/EventLoopThread.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/EventLoopThread.cc.o -MF CMakeFiles/mymuduo.dir/EventLoopThread.cc.o.d -o CMakeFiles/mymuduo.dir/EventLoopThread.cc.o -c /home/stu/muduoz/EventLoopThread.cc

CMakeFiles/mymuduo.dir/EventLoopThread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/EventLoopThread.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/EventLoopThread.cc > CMakeFiles/mymuduo.dir/EventLoopThread.cc.i

CMakeFiles/mymuduo.dir/EventLoopThread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/EventLoopThread.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/EventLoopThread.cc -o CMakeFiles/mymuduo.dir/EventLoopThread.cc.s

CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.o: /home/stu/muduoz/EventLoopThreadPool.cc
CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.o -MF CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.o.d -o CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.o -c /home/stu/muduoz/EventLoopThreadPool.cc

CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/EventLoopThreadPool.cc > CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.i

CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/EventLoopThreadPool.cc -o CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.s

CMakeFiles/mymuduo.dir/InetAddress.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/InetAddress.cc.o: /home/stu/muduoz/InetAddress.cc
CMakeFiles/mymuduo.dir/InetAddress.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/mymuduo.dir/InetAddress.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/InetAddress.cc.o -MF CMakeFiles/mymuduo.dir/InetAddress.cc.o.d -o CMakeFiles/mymuduo.dir/InetAddress.cc.o -c /home/stu/muduoz/InetAddress.cc

CMakeFiles/mymuduo.dir/InetAddress.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/InetAddress.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/InetAddress.cc > CMakeFiles/mymuduo.dir/InetAddress.cc.i

CMakeFiles/mymuduo.dir/InetAddress.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/InetAddress.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/InetAddress.cc -o CMakeFiles/mymuduo.dir/InetAddress.cc.s

CMakeFiles/mymuduo.dir/Logger.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Logger.cc.o: /home/stu/muduoz/Logger.cc
CMakeFiles/mymuduo.dir/Logger.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/mymuduo.dir/Logger.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Logger.cc.o -MF CMakeFiles/mymuduo.dir/Logger.cc.o.d -o CMakeFiles/mymuduo.dir/Logger.cc.o -c /home/stu/muduoz/Logger.cc

CMakeFiles/mymuduo.dir/Logger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Logger.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/Logger.cc > CMakeFiles/mymuduo.dir/Logger.cc.i

CMakeFiles/mymuduo.dir/Logger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Logger.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/Logger.cc -o CMakeFiles/mymuduo.dir/Logger.cc.s

CMakeFiles/mymuduo.dir/Poller.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Poller.cc.o: /home/stu/muduoz/Poller.cc
CMakeFiles/mymuduo.dir/Poller.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/mymuduo.dir/Poller.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Poller.cc.o -MF CMakeFiles/mymuduo.dir/Poller.cc.o.d -o CMakeFiles/mymuduo.dir/Poller.cc.o -c /home/stu/muduoz/Poller.cc

CMakeFiles/mymuduo.dir/Poller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Poller.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/Poller.cc > CMakeFiles/mymuduo.dir/Poller.cc.i

CMakeFiles/mymuduo.dir/Poller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Poller.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/Poller.cc -o CMakeFiles/mymuduo.dir/Poller.cc.s

CMakeFiles/mymuduo.dir/Socket.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Socket.cc.o: /home/stu/muduoz/Socket.cc
CMakeFiles/mymuduo.dir/Socket.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/mymuduo.dir/Socket.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Socket.cc.o -MF CMakeFiles/mymuduo.dir/Socket.cc.o.d -o CMakeFiles/mymuduo.dir/Socket.cc.o -c /home/stu/muduoz/Socket.cc

CMakeFiles/mymuduo.dir/Socket.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Socket.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/Socket.cc > CMakeFiles/mymuduo.dir/Socket.cc.i

CMakeFiles/mymuduo.dir/Socket.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Socket.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/Socket.cc -o CMakeFiles/mymuduo.dir/Socket.cc.s

CMakeFiles/mymuduo.dir/TcpServer.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/TcpServer.cc.o: /home/stu/muduoz/TcpServer.cc
CMakeFiles/mymuduo.dir/TcpServer.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/mymuduo.dir/TcpServer.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/TcpServer.cc.o -MF CMakeFiles/mymuduo.dir/TcpServer.cc.o.d -o CMakeFiles/mymuduo.dir/TcpServer.cc.o -c /home/stu/muduoz/TcpServer.cc

CMakeFiles/mymuduo.dir/TcpServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/TcpServer.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/TcpServer.cc > CMakeFiles/mymuduo.dir/TcpServer.cc.i

CMakeFiles/mymuduo.dir/TcpServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/TcpServer.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/TcpServer.cc -o CMakeFiles/mymuduo.dir/TcpServer.cc.s

CMakeFiles/mymuduo.dir/Tcpconnection.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Tcpconnection.cc.o: /home/stu/muduoz/Tcpconnection.cc
CMakeFiles/mymuduo.dir/Tcpconnection.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/mymuduo.dir/Tcpconnection.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Tcpconnection.cc.o -MF CMakeFiles/mymuduo.dir/Tcpconnection.cc.o.d -o CMakeFiles/mymuduo.dir/Tcpconnection.cc.o -c /home/stu/muduoz/Tcpconnection.cc

CMakeFiles/mymuduo.dir/Tcpconnection.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Tcpconnection.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/Tcpconnection.cc > CMakeFiles/mymuduo.dir/Tcpconnection.cc.i

CMakeFiles/mymuduo.dir/Tcpconnection.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Tcpconnection.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/Tcpconnection.cc -o CMakeFiles/mymuduo.dir/Tcpconnection.cc.s

CMakeFiles/mymuduo.dir/Thread.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Thread.cc.o: /home/stu/muduoz/Thread.cc
CMakeFiles/mymuduo.dir/Thread.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/mymuduo.dir/Thread.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Thread.cc.o -MF CMakeFiles/mymuduo.dir/Thread.cc.o.d -o CMakeFiles/mymuduo.dir/Thread.cc.o -c /home/stu/muduoz/Thread.cc

CMakeFiles/mymuduo.dir/Thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Thread.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/Thread.cc > CMakeFiles/mymuduo.dir/Thread.cc.i

CMakeFiles/mymuduo.dir/Thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Thread.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/Thread.cc -o CMakeFiles/mymuduo.dir/Thread.cc.s

CMakeFiles/mymuduo.dir/Timestamp.cc.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Timestamp.cc.o: /home/stu/muduoz/Timestamp.cc
CMakeFiles/mymuduo.dir/Timestamp.cc.o: CMakeFiles/mymuduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/mymuduo.dir/Timestamp.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mymuduo.dir/Timestamp.cc.o -MF CMakeFiles/mymuduo.dir/Timestamp.cc.o.d -o CMakeFiles/mymuduo.dir/Timestamp.cc.o -c /home/stu/muduoz/Timestamp.cc

CMakeFiles/mymuduo.dir/Timestamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Timestamp.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stu/muduoz/Timestamp.cc > CMakeFiles/mymuduo.dir/Timestamp.cc.i

CMakeFiles/mymuduo.dir/Timestamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Timestamp.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stu/muduoz/Timestamp.cc -o CMakeFiles/mymuduo.dir/Timestamp.cc.s

# Object files for target mymuduo
mymuduo_OBJECTS = \
"CMakeFiles/mymuduo.dir/Acceptor.cc.o" \
"CMakeFiles/mymuduo.dir/Buffer.cc.o" \
"CMakeFiles/mymuduo.dir/Channel.cc.o" \
"CMakeFiles/mymuduo.dir/CurrentThread.cc.o" \
"CMakeFiles/mymuduo.dir/DefaultPoller.cc.o" \
"CMakeFiles/mymuduo.dir/EPollPoller.cc.o" \
"CMakeFiles/mymuduo.dir/EventLoop.cc.o" \
"CMakeFiles/mymuduo.dir/EventLoopThread.cc.o" \
"CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.o" \
"CMakeFiles/mymuduo.dir/InetAddress.cc.o" \
"CMakeFiles/mymuduo.dir/Logger.cc.o" \
"CMakeFiles/mymuduo.dir/Poller.cc.o" \
"CMakeFiles/mymuduo.dir/Socket.cc.o" \
"CMakeFiles/mymuduo.dir/TcpServer.cc.o" \
"CMakeFiles/mymuduo.dir/Tcpconnection.cc.o" \
"CMakeFiles/mymuduo.dir/Thread.cc.o" \
"CMakeFiles/mymuduo.dir/Timestamp.cc.o"

# External object files for target mymuduo
mymuduo_EXTERNAL_OBJECTS =

/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Acceptor.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Buffer.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Channel.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/CurrentThread.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/DefaultPoller.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/EPollPoller.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/EventLoop.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/EventLoopThread.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/EventLoopThreadPool.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/InetAddress.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Logger.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Poller.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Socket.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/TcpServer.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Tcpconnection.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Thread.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Timestamp.cc.o
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/build.make
/home/stu/muduoz/lib/libmymuduo.so: CMakeFiles/mymuduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/stu/muduoz/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX shared library /home/stu/muduoz/lib/libmymuduo.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mymuduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mymuduo.dir/build: /home/stu/muduoz/lib/libmymuduo.so
.PHONY : CMakeFiles/mymuduo.dir/build

CMakeFiles/mymuduo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mymuduo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mymuduo.dir/clean

CMakeFiles/mymuduo.dir/depend:
	cd /home/stu/muduoz/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stu/muduoz /home/stu/muduoz /home/stu/muduoz/build /home/stu/muduoz/build /home/stu/muduoz/build/CMakeFiles/mymuduo.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/mymuduo.dir/depend

