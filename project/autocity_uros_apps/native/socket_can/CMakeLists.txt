cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(socket_can)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}")
SET( LIBRARY_OUTPUT_PATH "${WORKSPACE}/lib")

set( TARGET_LIB socket_can )

include_directories(
	include
	)

file(GLOB SRCS "src/*.c")
list(SORT SRCS)

add_library(${TARGET_LIB} ${SRCS} )
