# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/build"

# Include any dependencies generated for this target.
include CMakeFiles/lab03.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab03.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab03.dir/flags.make

CMakeFiles/lab03.dir/main.cpp.o: CMakeFiles/lab03.dir/flags.make
CMakeFiles/lab03.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab03.dir/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab03.dir/main.cpp.o -c "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/main.cpp"

CMakeFiles/lab03.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab03.dir/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/main.cpp" > CMakeFiles/lab03.dir/main.cpp.i

CMakeFiles/lab03.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab03.dir/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/main.cpp" -o CMakeFiles/lab03.dir/main.cpp.s

CMakeFiles/lab03.dir/Blur.cpp.o: CMakeFiles/lab03.dir/flags.make
CMakeFiles/lab03.dir/Blur.cpp.o: ../Blur.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lab03.dir/Blur.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab03.dir/Blur.cpp.o -c "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/Blur.cpp"

CMakeFiles/lab03.dir/Blur.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab03.dir/Blur.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/Blur.cpp" > CMakeFiles/lab03.dir/Blur.cpp.i

CMakeFiles/lab03.dir/Blur.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab03.dir/Blur.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/Blur.cpp" -o CMakeFiles/lab03.dir/Blur.cpp.s

CMakeFiles/lab03.dir/Convolution.cpp.o: CMakeFiles/lab03.dir/flags.make
CMakeFiles/lab03.dir/Convolution.cpp.o: ../Convolution.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/lab03.dir/Convolution.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab03.dir/Convolution.cpp.o -c "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/Convolution.cpp"

CMakeFiles/lab03.dir/Convolution.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab03.dir/Convolution.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/Convolution.cpp" > CMakeFiles/lab03.dir/Convolution.cpp.i

CMakeFiles/lab03.dir/Convolution.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab03.dir/Convolution.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/Convolution.cpp" -o CMakeFiles/lab03.dir/Convolution.cpp.s

# Object files for target lab03
lab03_OBJECTS = \
"CMakeFiles/lab03.dir/main.cpp.o" \
"CMakeFiles/lab03.dir/Blur.cpp.o" \
"CMakeFiles/lab03.dir/Convolution.cpp.o"

# External object files for target lab03
lab03_EXTERNAL_OBJECTS =

lab03: CMakeFiles/lab03.dir/main.cpp.o
lab03: CMakeFiles/lab03.dir/Blur.cpp.o
lab03: CMakeFiles/lab03.dir/Convolution.cpp.o
lab03: CMakeFiles/lab03.dir/build.make
lab03: /usr/local/lib/libopencv_gapi.4.5.1.dylib
lab03: /usr/local/lib/libopencv_highgui.4.5.1.dylib
lab03: /usr/local/lib/libopencv_ml.4.5.1.dylib
lab03: /usr/local/lib/libopencv_objdetect.4.5.1.dylib
lab03: /usr/local/lib/libopencv_photo.4.5.1.dylib
lab03: /usr/local/lib/libopencv_stitching.4.5.1.dylib
lab03: /usr/local/lib/libopencv_video.4.5.1.dylib
lab03: /usr/local/lib/libopencv_videoio.4.5.1.dylib
lab03: /usr/local/lib/libopencv_dnn.4.5.1.dylib
lab03: /usr/local/lib/libopencv_imgcodecs.4.5.1.dylib
lab03: /usr/local/lib/libopencv_calib3d.4.5.1.dylib
lab03: /usr/local/lib/libopencv_features2d.4.5.1.dylib
lab03: /usr/local/lib/libopencv_flann.4.5.1.dylib
lab03: /usr/local/lib/libopencv_imgproc.4.5.1.dylib
lab03: /usr/local/lib/libopencv_core.4.5.1.dylib
lab03: CMakeFiles/lab03.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable lab03"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab03.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab03.dir/build: lab03

.PHONY : CMakeFiles/lab03.dir/build

CMakeFiles/lab03.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab03.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab03.dir/clean

CMakeFiles/lab03.dir/depend:
	cd "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise" "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise" "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/build" "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/build" "/Users/lap14153/Documents/study/digital-image-processing/Image And Video Processing/Lab/Lab03/exercise/build/CMakeFiles/lab03.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/lab03.dir/depend

