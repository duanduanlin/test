cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(hello_world)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
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

file(GLOB FIDL_SRCS_HELLOWORLD "${WORKSPACE}/fidl/src-gen/v1/hello_world/*.cpp")
list(SORT FIDL_SRCS_HELLOWORLD)

add_executable(HelloWorldClient
	src/HelloWorldClient.cpp
	${FIDL_SRCS_HELLOWORLD}
	)
target_link_libraries(HelloWorldClient CommonAPI CommonAPI-DBus dbus-1)

add_executable(HelloWorldService
	src/HelloWorldService.cpp
	src/HelloWorldStubImpl.cpp
	${FIDL_SRCS_HELLOWORLD}
	)
target_link_libraries(HelloWorldService CommonAPI CommonAPI-DBus dbus-1)
