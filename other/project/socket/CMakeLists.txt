cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(socket_test)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -std=c++0x")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/build/output/apps/bin")

set( TARGET_BIN_S socket_test_s )
set( TARGET_BIN_C socket_test_c )

include_directories(
	include
	)

file(GLOB SRC_S "src/socket_test_server.cpp")
list(SORT SRC_S)

file(GLOB SRC_C "src/socket_test_client.cpp")
list(SORT SRC_C)

add_executable(${TARGET_BIN_S} ${SRC_S} )
add_executable(${TARGET_BIN_C} ${SRC_C} )
