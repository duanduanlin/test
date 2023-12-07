cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(dl_test)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -std=c++0x")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( LIBRARY_OUTPUT_PATH "${WORKSPACE}/build/output/apps/lib")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/build/output/apps/bin")

set( TARGET_BIN dl_test )
set( TARGET_LIB caculate )

include_directories(
	include
	)

file(GLOB SRCS_LIB "src/caculate.cpp")
list(SORT SRCS_LIB)

add_library(${TARGET_LIB} SHARED ${SRCS_LIB} )

file(GLOB SRCS "src/dl_test.cpp")
list(SORT SRCS)

add_executable(${TARGET_BIN} ${SRCS} )
target_link_libraries( ${TARGET_BIN} dl)
