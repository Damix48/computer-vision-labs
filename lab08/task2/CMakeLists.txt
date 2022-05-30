cmake_minimum_required(VERSION 2.8)
project( lab08_task2 )
find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} include/ )

add_library(utils_opencv src/utils_opencv.cpp include/utils_opencv.h)

add_executable( main main.cpp )
target_link_libraries( main ${OpenCV_LIBS} utils_opencv)