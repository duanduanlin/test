cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(rpc_func)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -std=c++0x")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( LIBRARY_OUTPUT_PATH "${WORKSPACE}/build/output/apps/lib")

set( TARGET_LIB rpc_func )

include_directories(
	include
	)

file(GLOB SRCS "src/*.cpp")
list(SORT SRCS)

add_library(${TARGET_LIB} SHARED ${SRCS} )
