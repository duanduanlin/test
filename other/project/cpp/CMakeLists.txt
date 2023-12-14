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
set( TARGET_BIN_ATOMIC cpp_atomic )
set( TARGET_BIN_LIST cpp_list )
set( TARGET_BIN_OPERATOR cpp_operator )
set( TARGET_BIN_HEXSTR cpp_hexStr )
set( TARGET_BIN_POLL cpp_poll )
set( TARGET_BIN_EPOLL cpp_epoll )

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

file(GLOB SRCS_ATOMIC "src/atomic_test.cpp")
list(SORT SRCS_ATOMIC)

add_executable(${TARGET_BIN_ATOMIC} ${SRCS_ATOMIC} )

file(GLOB SRCS_LIST "src/list_test.cpp")
list(SORT SRCS_LIST)

add_executable(${TARGET_BIN_LIST} ${SRCS_LIST} )

file(GLOB SRCS_OPERATOR "src/operator_test.cpp")
list(SORT SRCS_OPERATOR)

add_executable(${TARGET_BIN_OPERATOR} ${SRCS_OPERATOR} )

file(GLOB SRCS_HEXSTR "src/hexStr_test.cpp")
list(SORT SRCS_HEXSTR)

add_executable(${TARGET_BIN_HEXSTR} ${SRCS_HEXSTR} )

file(GLOB SRCS_POLL "src/poll_test.cpp")
list(SORT SRCS_POLL)

add_executable(${TARGET_BIN_POLL} ${SRCS_POLL} )

file(GLOB SRCS_EPOLL "src/epoll_test.cpp")
list(SORT SRCS_EPOLL)

add_executable(${TARGET_BIN_EPOLL} ${SRCS_EPOLL} )
