cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(hello_world)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")
#设置输出路径
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../../output/apps/bin")

include_directories(
	include
	src-gen
	../../3rdlibs/capicxx-core-runtime/include
	../../3rdlibs/capicxx-dbus-runtime/include
	../../3rdlibs/dbus-1.10.10
	)

add_executable(HelloWorldClient
	src/HelloWorldClient.cpp
	src-gen/v1/hello_world/HelloWorldDBusProxy.cpp
	src-gen/v1/hello_world/HelloWorldDBusDeployment.cpp
	)
target_link_libraries(HelloWorldClient CommonAPI CommonAPI-DBus dbus-1)

add_executable(HelloWorldService
	src/HelloWorldService.cpp
	src/HelloWorldStubImpl.cpp
	src-gen/v1/hello_world/HelloWorldDBusStubAdapter.cpp

	src-gen/v1/hello_world/HelloWorldDBusDeployment.cpp
	)
target_link_libraries(HelloWorldService CommonAPI CommonAPI-DBus dbus-1)
