cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(native)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

message(${CMAKE_HOST_SYSTEM_NAME})
message(${CMAKE_HOST_SYSTEM_PROCESSOR})

#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}")
SET( LIBRARY_OUTPUT_PATH "${WORKSPACE}/")

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
    message("this is aarch64 cpu")
    set( TARGET_LIB native-aarch64 )
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
	message("this is x86_64 cpu")
    set( TARGET_LIB native-x86_64 )
endif()



include_directories(
	socket_can/include
    ufile/include
    backtrace/include
    ringbuffer/include
	)

file(GLOB SOCKET_CAN_SRCS "socket_can/src/*.c")
list(SORT SOCKET_CAN_SRCS)

file(GLOB UFILE_SRCS "ufile/src/*.c")
list(SORT UFILE_SRCS)

file(GLOB BACKTRACE_SRCS "backtrace/src/*.c")
list(SORT BACKTRACE_SRCS)

file(GLOB RINGBUFFER_SRCS "ringbuffer/src/*.c")
list(SORT RINGBUFFER_SRCS)

add_library(${TARGET_LIB} ${SOCKET_CAN_SRCS} ${UFILE_SRCS} ${BACKTRACE_SRCS} ${RINGBUFFER_SRCS})
