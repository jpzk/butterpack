cmake_minimum_required(VERSION 2.8)
project( butterpack )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( butterpack src/butterpack_codec.cpp src/butterpack.cpp src/main.cpp)
target_include_directories (butterpack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries( butterpack ${OpenCV_LIBS} )
