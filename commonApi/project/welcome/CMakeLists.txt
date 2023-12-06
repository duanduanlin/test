cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(welcome)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -std=c++0x")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/output/apps/bin")

include_directories(
	include
	${WORKSPACE}/fidl/src-gen/
	${WORKSPACE}/3rdlibs/capicxx-core-runtime/include
	${WORKSPACE}/3rdlibs/capicxx-dbus-runtime/include
	${WORKSPACE}/3rdlibs/dbus-1.10.10
	)

file(GLOB FIDL_SRCS_WELCOME "${WORKSPACE}/fidl/src-gen/v1/welcome/*.cpp")
list(SORT FIDL_SRCS_WELCOME)

add_executable(WelcomeClient
	src/WelcomeClient.cpp
	${FIDL_SRCS_WELCOME}
	)
target_link_libraries(WelcomeClient CommonAPI CommonAPI-DBus dbus-1)

add_executable(WelcomeService
	src/WelcomeService.cpp
	src/WelcomeStubImpl.cpp
	${FIDL_SRCS_WELCOME}
	)
target_link_libraries(WelcomeService CommonAPI CommonAPI-DBus dbus-1)
