cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(cpp_test)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -std=c++0x")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/build/output/apps/bin")

set( TARGET_BIN_MOVE cpp_move )
set( TARGET_BIN_CB cpp_callback )
set( TARGET_BIN_TEMPLATE cpp_template )
set( TARGET_BIN_ENUM cpp_enum )
set( TARGET_BIN_LAMBDA cpp_lambda )
set( TARGET_BIN_SYSCALL cpp_syscall )

include_directories(
	include
	)

file(GLOB SRCS_MOVE "src/move_test.cpp")
list(SORT SRCS_MOVE)

add_executable(${TARGET_BIN_MOVE} ${SRCS_MOVE} )

file(GLOB SRCS_CB "src/callback_test.cpp")
list(SORT SRCS_CB)

add_executable(${TARGET_BIN_CB} ${SRCS_CB} )

file(GLOB SRCS_TEMPLATE "src/template_test.cpp")
list(SORT SRCS_TEMPLATE)

add_executable(${TARGET_BIN_TEMPLATE} ${SRCS_TEMPLATE} )

file(GLOB SRCS_ENUM "src/enum_test.cpp")
list(SORT SRCS_ENUM)

add_executable(${TARGET_BIN_ENUM} ${SRCS_ENUM} )

file(GLOB SRCS_LAMBDA "src/lambda_test.cpp")
list(SORT SRCS_LAMBDA)

add_executable(${TARGET_BIN_LAMBDA} ${SRCS_LAMBDA} )

file(GLOB SRCS_SYSCALL "src/syscall_test.cpp")
list(SORT SRCS_SYSCALL)

add_executable(${TARGET_BIN_SYSCALL} ${SRCS_SYSCALL} )
