# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\ProgramFiles\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\ProgramFiles\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\semestr_3\zpo\clion_projects\tsp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\semestr_3\zpo\clion_projects\tsp\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tsp.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/tsp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tsp.dir/flags.make

CMakeFiles/tsp.dir/src/tsp_setup.cpp.obj: CMakeFiles/tsp.dir/flags.make
CMakeFiles/tsp.dir/src/tsp_setup.cpp.obj: CMakeFiles/tsp.dir/includes_CXX.rsp
CMakeFiles/tsp.dir/src/tsp_setup.cpp.obj: ../src/tsp_setup.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\semestr_3\zpo\clion_projects\tsp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tsp.dir/src/tsp_setup.cpp.obj"
	D:\ProgramFiles\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\tsp.dir\src\tsp_setup.cpp.obj -c D:\semestr_3\zpo\clion_projects\tsp\src\tsp_setup.cpp

CMakeFiles/tsp.dir/src/tsp_setup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tsp.dir/src/tsp_setup.cpp.i"
	D:\ProgramFiles\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\semestr_3\zpo\clion_projects\tsp\src\tsp_setup.cpp > CMakeFiles\tsp.dir\src\tsp_setup.cpp.i

CMakeFiles/tsp.dir/src/tsp_setup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tsp.dir/src/tsp_setup.cpp.s"
	D:\ProgramFiles\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\semestr_3\zpo\clion_projects\tsp\src\tsp_setup.cpp -o CMakeFiles\tsp.dir\src\tsp_setup.cpp.s

CMakeFiles/tsp.dir/src/TSP.cpp.obj: CMakeFiles/tsp.dir/flags.make
CMakeFiles/tsp.dir/src/TSP.cpp.obj: CMakeFiles/tsp.dir/includes_CXX.rsp
CMakeFiles/tsp.dir/src/TSP.cpp.obj: ../src/TSP.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\semestr_3\zpo\clion_projects\tsp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tsp.dir/src/TSP.cpp.obj"
	D:\ProgramFiles\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\tsp.dir\src\TSP.cpp.obj -c D:\semestr_3\zpo\clion_projects\tsp\src\TSP.cpp

CMakeFiles/tsp.dir/src/TSP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tsp.dir/src/TSP.cpp.i"
	D:\ProgramFiles\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\semestr_3\zpo\clion_projects\tsp\src\TSP.cpp > CMakeFiles\tsp.dir\src\TSP.cpp.i

CMakeFiles/tsp.dir/src/TSP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tsp.dir/src/TSP.cpp.s"
	D:\ProgramFiles\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\semestr_3\zpo\clion_projects\tsp\src\TSP.cpp -o CMakeFiles\tsp.dir\src\TSP.cpp.s

CMakeFiles/tsp.dir/main.cpp.obj: CMakeFiles/tsp.dir/flags.make
CMakeFiles/tsp.dir/main.cpp.obj: CMakeFiles/tsp.dir/includes_CXX.rsp
CMakeFiles/tsp.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\semestr_3\zpo\clion_projects\tsp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/tsp.dir/main.cpp.obj"
	D:\ProgramFiles\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\tsp.dir\main.cpp.obj -c D:\semestr_3\zpo\clion_projects\tsp\main.cpp

CMakeFiles/tsp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tsp.dir/main.cpp.i"
	D:\ProgramFiles\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\semestr_3\zpo\clion_projects\tsp\main.cpp > CMakeFiles\tsp.dir\main.cpp.i

CMakeFiles/tsp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tsp.dir/main.cpp.s"
	D:\ProgramFiles\msys2\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\semestr_3\zpo\clion_projects\tsp\main.cpp -o CMakeFiles\tsp.dir\main.cpp.s

# Object files for target tsp
tsp_OBJECTS = \
"CMakeFiles/tsp.dir/src/tsp_setup.cpp.obj" \
"CMakeFiles/tsp.dir/src/TSP.cpp.obj" \
"CMakeFiles/tsp.dir/main.cpp.obj"

# External object files for target tsp
tsp_EXTERNAL_OBJECTS =

tsp.exe: CMakeFiles/tsp.dir/src/tsp_setup.cpp.obj
tsp.exe: CMakeFiles/tsp.dir/src/TSP.cpp.obj
tsp.exe: CMakeFiles/tsp.dir/main.cpp.obj
tsp.exe: CMakeFiles/tsp.dir/build.make
tsp.exe: CMakeFiles/tsp.dir/linklibs.rsp
tsp.exe: CMakeFiles/tsp.dir/objects1.rsp
tsp.exe: CMakeFiles/tsp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\semestr_3\zpo\clion_projects\tsp\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable tsp.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tsp.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tsp.dir/build: tsp.exe
.PHONY : CMakeFiles/tsp.dir/build

CMakeFiles/tsp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\tsp.dir\cmake_clean.cmake
.PHONY : CMakeFiles/tsp.dir/clean

CMakeFiles/tsp.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\semestr_3\zpo\clion_projects\tsp D:\semestr_3\zpo\clion_projects\tsp D:\semestr_3\zpo\clion_projects\tsp\cmake-build-debug D:\semestr_3\zpo\clion_projects\tsp\cmake-build-debug D:\semestr_3\zpo\clion_projects\tsp\cmake-build-debug\CMakeFiles\tsp.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tsp.dir/depend

