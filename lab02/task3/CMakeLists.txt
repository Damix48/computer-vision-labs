cmake_minimum_required(VERSION 2.8)
project( lab01_task2 )

find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} include/)

add_library(filters src/filters.cpp include/filters.h)

add_executable( main main.cpp)

target_link_libraries( main ${OpenCV_LIBS} )
target_link_libraries( main filters )
