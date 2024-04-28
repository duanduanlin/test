cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(section_test)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -std=c++0x -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/s.lds")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/build/output/apps/bin")

set( TARGET_BIN section_test )

include_directories(
	include
	)

file(GLOB SRCS "src/*.cpp")
list(SORT SRCS)

add_executable(${TARGET_BIN} ${SRCS} )
