# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/workspace/AI-Todo/Backend/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/workspace/AI-Todo/Backend/src/build

# Include any dependencies generated for this target.
include server/CMakeFiles/ChatServer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include server/CMakeFiles/ChatServer.dir/compiler_depend.make

# Include the progress variables for this target.
include server/CMakeFiles/ChatServer.dir/progress.make

# Include the compile flags for this target's objects.
include server/CMakeFiles/ChatServer.dir/flags.make

server/CMakeFiles/ChatServer.dir/chatservice.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/chatservice.o: ../server/chatservice.cpp
server/CMakeFiles/ChatServer.dir/chatservice.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object server/CMakeFiles/ChatServer.dir/chatservice.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/chatservice.o -MF CMakeFiles/ChatServer.dir/chatservice.o.d -o CMakeFiles/ChatServer.dir/chatservice.o -c /home/workspace/AI-Todo/Backend/src/server/chatservice.cpp

server/CMakeFiles/ChatServer.dir/chatservice.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/chatservice.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/chatservice.cpp > CMakeFiles/ChatServer.dir/chatservice.i

server/CMakeFiles/ChatServer.dir/chatservice.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/chatservice.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/chatservice.cpp -o CMakeFiles/ChatServer.dir/chatservice.s

server/CMakeFiles/ChatServer.dir/gptcurl.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/gptcurl.o: ../server/gptcurl.cpp
server/CMakeFiles/ChatServer.dir/gptcurl.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object server/CMakeFiles/ChatServer.dir/gptcurl.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/gptcurl.o -MF CMakeFiles/ChatServer.dir/gptcurl.o.d -o CMakeFiles/ChatServer.dir/gptcurl.o -c /home/workspace/AI-Todo/Backend/src/server/gptcurl.cpp

server/CMakeFiles/ChatServer.dir/gptcurl.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/gptcurl.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/gptcurl.cpp > CMakeFiles/ChatServer.dir/gptcurl.i

server/CMakeFiles/ChatServer.dir/gptcurl.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/gptcurl.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/gptcurl.cpp -o CMakeFiles/ChatServer.dir/gptcurl.s

server/CMakeFiles/ChatServer.dir/main.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/main.o: ../server/main.cpp
server/CMakeFiles/ChatServer.dir/main.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object server/CMakeFiles/ChatServer.dir/main.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/main.o -MF CMakeFiles/ChatServer.dir/main.o.d -o CMakeFiles/ChatServer.dir/main.o -c /home/workspace/AI-Todo/Backend/src/server/main.cpp

server/CMakeFiles/ChatServer.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/main.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/main.cpp > CMakeFiles/ChatServer.dir/main.i

server/CMakeFiles/ChatServer.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/main.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/main.cpp -o CMakeFiles/ChatServer.dir/main.s

server/CMakeFiles/ChatServer.dir/note.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/note.o: ../server/note.cpp
server/CMakeFiles/ChatServer.dir/note.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object server/CMakeFiles/ChatServer.dir/note.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/note.o -MF CMakeFiles/ChatServer.dir/note.o.d -o CMakeFiles/ChatServer.dir/note.o -c /home/workspace/AI-Todo/Backend/src/server/note.cpp

server/CMakeFiles/ChatServer.dir/note.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/note.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/note.cpp > CMakeFiles/ChatServer.dir/note.i

server/CMakeFiles/ChatServer.dir/note.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/note.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/note.cpp -o CMakeFiles/ChatServer.dir/note.s

server/CMakeFiles/ChatServer.dir/public.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/public.o: ../server/public.cpp
server/CMakeFiles/ChatServer.dir/public.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object server/CMakeFiles/ChatServer.dir/public.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/public.o -MF CMakeFiles/ChatServer.dir/public.o.d -o CMakeFiles/ChatServer.dir/public.o -c /home/workspace/AI-Todo/Backend/src/server/public.cpp

server/CMakeFiles/ChatServer.dir/public.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/public.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/public.cpp > CMakeFiles/ChatServer.dir/public.i

server/CMakeFiles/ChatServer.dir/public.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/public.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/public.cpp -o CMakeFiles/ChatServer.dir/public.s

server/CMakeFiles/ChatServer.dir/db/db.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/db/db.o: ../server/db/db.cpp
server/CMakeFiles/ChatServer.dir/db/db.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object server/CMakeFiles/ChatServer.dir/db/db.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/db/db.o -MF CMakeFiles/ChatServer.dir/db/db.o.d -o CMakeFiles/ChatServer.dir/db/db.o -c /home/workspace/AI-Todo/Backend/src/server/db/db.cpp

server/CMakeFiles/ChatServer.dir/db/db.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/db/db.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/db/db.cpp > CMakeFiles/ChatServer.dir/db/db.i

server/CMakeFiles/ChatServer.dir/db/db.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/db/db.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/db/db.cpp -o CMakeFiles/ChatServer.dir/db/db.s

server/CMakeFiles/ChatServer.dir/model/articlemodel.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/model/articlemodel.o: ../server/model/articlemodel.cpp
server/CMakeFiles/ChatServer.dir/model/articlemodel.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object server/CMakeFiles/ChatServer.dir/model/articlemodel.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/model/articlemodel.o -MF CMakeFiles/ChatServer.dir/model/articlemodel.o.d -o CMakeFiles/ChatServer.dir/model/articlemodel.o -c /home/workspace/AI-Todo/Backend/src/server/model/articlemodel.cpp

server/CMakeFiles/ChatServer.dir/model/articlemodel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/model/articlemodel.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/model/articlemodel.cpp > CMakeFiles/ChatServer.dir/model/articlemodel.i

server/CMakeFiles/ChatServer.dir/model/articlemodel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/model/articlemodel.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/model/articlemodel.cpp -o CMakeFiles/ChatServer.dir/model/articlemodel.s

server/CMakeFiles/ChatServer.dir/model/usermodel.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/model/usermodel.o: ../server/model/usermodel.cpp
server/CMakeFiles/ChatServer.dir/model/usermodel.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object server/CMakeFiles/ChatServer.dir/model/usermodel.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/model/usermodel.o -MF CMakeFiles/ChatServer.dir/model/usermodel.o.d -o CMakeFiles/ChatServer.dir/model/usermodel.o -c /home/workspace/AI-Todo/Backend/src/server/model/usermodel.cpp

server/CMakeFiles/ChatServer.dir/model/usermodel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/model/usermodel.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/model/usermodel.cpp > CMakeFiles/ChatServer.dir/model/usermodel.i

server/CMakeFiles/ChatServer.dir/model/usermodel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/model/usermodel.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/model/usermodel.cpp -o CMakeFiles/ChatServer.dir/model/usermodel.s

server/CMakeFiles/ChatServer.dir/http/httpcontext.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/http/httpcontext.o: ../server/http/httpcontext.cpp
server/CMakeFiles/ChatServer.dir/http/httpcontext.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object server/CMakeFiles/ChatServer.dir/http/httpcontext.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/http/httpcontext.o -MF CMakeFiles/ChatServer.dir/http/httpcontext.o.d -o CMakeFiles/ChatServer.dir/http/httpcontext.o -c /home/workspace/AI-Todo/Backend/src/server/http/httpcontext.cpp

server/CMakeFiles/ChatServer.dir/http/httpcontext.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/http/httpcontext.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/http/httpcontext.cpp > CMakeFiles/ChatServer.dir/http/httpcontext.i

server/CMakeFiles/ChatServer.dir/http/httpcontext.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/http/httpcontext.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/http/httpcontext.cpp -o CMakeFiles/ChatServer.dir/http/httpcontext.s

server/CMakeFiles/ChatServer.dir/http/httprequest.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/http/httprequest.o: ../server/http/httprequest.cpp
server/CMakeFiles/ChatServer.dir/http/httprequest.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object server/CMakeFiles/ChatServer.dir/http/httprequest.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/http/httprequest.o -MF CMakeFiles/ChatServer.dir/http/httprequest.o.d -o CMakeFiles/ChatServer.dir/http/httprequest.o -c /home/workspace/AI-Todo/Backend/src/server/http/httprequest.cpp

server/CMakeFiles/ChatServer.dir/http/httprequest.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/http/httprequest.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/http/httprequest.cpp > CMakeFiles/ChatServer.dir/http/httprequest.i

server/CMakeFiles/ChatServer.dir/http/httprequest.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/http/httprequest.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/http/httprequest.cpp -o CMakeFiles/ChatServer.dir/http/httprequest.s

server/CMakeFiles/ChatServer.dir/http/httpresponse.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/http/httpresponse.o: ../server/http/httpresponse.cpp
server/CMakeFiles/ChatServer.dir/http/httpresponse.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object server/CMakeFiles/ChatServer.dir/http/httpresponse.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/http/httpresponse.o -MF CMakeFiles/ChatServer.dir/http/httpresponse.o.d -o CMakeFiles/ChatServer.dir/http/httpresponse.o -c /home/workspace/AI-Todo/Backend/src/server/http/httpresponse.cpp

server/CMakeFiles/ChatServer.dir/http/httpresponse.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/http/httpresponse.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/http/httpresponse.cpp > CMakeFiles/ChatServer.dir/http/httpresponse.i

server/CMakeFiles/ChatServer.dir/http/httpresponse.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/http/httpresponse.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/http/httpresponse.cpp -o CMakeFiles/ChatServer.dir/http/httpresponse.s

server/CMakeFiles/ChatServer.dir/http/httpserver.o: server/CMakeFiles/ChatServer.dir/flags.make
server/CMakeFiles/ChatServer.dir/http/httpserver.o: ../server/http/httpserver.cpp
server/CMakeFiles/ChatServer.dir/http/httpserver.o: server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object server/CMakeFiles/ChatServer.dir/http/httpserver.o"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT server/CMakeFiles/ChatServer.dir/http/httpserver.o -MF CMakeFiles/ChatServer.dir/http/httpserver.o.d -o CMakeFiles/ChatServer.dir/http/httpserver.o -c /home/workspace/AI-Todo/Backend/src/server/http/httpserver.cpp

server/CMakeFiles/ChatServer.dir/http/httpserver.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/http/httpserver.i"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/workspace/AI-Todo/Backend/src/server/http/httpserver.cpp > CMakeFiles/ChatServer.dir/http/httpserver.i

server/CMakeFiles/ChatServer.dir/http/httpserver.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/http/httpserver.s"
	cd /home/workspace/AI-Todo/Backend/src/build/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/workspace/AI-Todo/Backend/src/server/http/httpserver.cpp -o CMakeFiles/ChatServer.dir/http/httpserver.s

# Object files for target ChatServer
ChatServer_OBJECTS = \
"CMakeFiles/ChatServer.dir/chatservice.o" \
"CMakeFiles/ChatServer.dir/gptcurl.o" \
"CMakeFiles/ChatServer.dir/main.o" \
"CMakeFiles/ChatServer.dir/note.o" \
"CMakeFiles/ChatServer.dir/public.o" \
"CMakeFiles/ChatServer.dir/db/db.o" \
"CMakeFiles/ChatServer.dir/model/articlemodel.o" \
"CMakeFiles/ChatServer.dir/model/usermodel.o" \
"CMakeFiles/ChatServer.dir/http/httpcontext.o" \
"CMakeFiles/ChatServer.dir/http/httprequest.o" \
"CMakeFiles/ChatServer.dir/http/httpresponse.o" \
"CMakeFiles/ChatServer.dir/http/httpserver.o"

# External object files for target ChatServer
ChatServer_EXTERNAL_OBJECTS =

server/ChatServer: server/CMakeFiles/ChatServer.dir/chatservice.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/gptcurl.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/main.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/note.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/public.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/db/db.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/model/articlemodel.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/model/usermodel.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/http/httpcontext.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/http/httprequest.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/http/httpresponse.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/http/httpserver.o
server/ChatServer: server/CMakeFiles/ChatServer.dir/build.make
server/ChatServer: server/CMakeFiles/ChatServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/workspace/AI-Todo/Backend/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable ChatServer"
	cd /home/workspace/AI-Todo/Backend/src/build/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ChatServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
server/CMakeFiles/ChatServer.dir/build: server/ChatServer
.PHONY : server/CMakeFiles/ChatServer.dir/build

server/CMakeFiles/ChatServer.dir/clean:
	cd /home/workspace/AI-Todo/Backend/src/build/server && $(CMAKE_COMMAND) -P CMakeFiles/ChatServer.dir/cmake_clean.cmake
.PHONY : server/CMakeFiles/ChatServer.dir/clean

server/CMakeFiles/ChatServer.dir/depend:
	cd /home/workspace/AI-Todo/Backend/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/workspace/AI-Todo/Backend/src /home/workspace/AI-Todo/Backend/src/server /home/workspace/AI-Todo/Backend/src/build /home/workspace/AI-Todo/Backend/src/build/server /home/workspace/AI-Todo/Backend/src/build/server/CMakeFiles/ChatServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : server/CMakeFiles/ChatServer.dir/depend

