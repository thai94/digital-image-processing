cmake_minimum_required(VERSION 3.0.0)
project(exercise01 VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(exercise01 main.cpp Converter.h Converter.cpp ColorTransformer.h ColorTransformer.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# Tell compiler to use C++ 14 features which is needed because
# Clang version is often behind in the XCode installation
set(CMAKE_CXX_STANDARD 14)

# set OpenCV_DIR variable equal to the path to the cmake
# files within the previously installed opencv program
set(OpenCV_DIR /usr/local/include/opencv4)

# configure the necessary common CMake environment variables
# needed to include and link the OpenCV program into this
# demo project, namely OpenCV_INCLUDE_DIRS and OpenCV_LIBS
find_package( OpenCV REQUIRED )

# tell it to link the executable target against OpenCV
target_link_libraries(exercise01 ${OpenCV_LIBS} )
include(CPack)