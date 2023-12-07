cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(cpp_test)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -std=c++0x")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/build/output/apps/bin")

set( TARGET_BIN cpp_move )

include_directories(
	include
	)

file(GLOB SRCS_MOVE "src/move_test.cpp")
list(SORT SRCS_MOVE)

add_executable(${TARGET_BIN} ${SRCS_MOVE} )
