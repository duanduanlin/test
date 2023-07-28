cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(good_bye)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -std=c++0x")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../..")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/output/apps/bin")

include_directories(
	include
	${WORKSPACE}/fidl/src-gen
	${WORKSPACE}/3rdlibs/capicxx-core-runtime/include
	${WORKSPACE}/3rdlibs/capicxx-dbus-runtime/include
	${WORKSPACE}/3rdlibs/dbus-1.10.10
	)

file(GLOB FIDL_SRCS_GOODBYE "${WORKSPACE}/fidl/src-gen/v1/good_bye/*.cpp")
list(SORT FIDL_SRCS_GOODBYE)

file(GLOB FIDL_SRCS_HELLOWORLD "${WORKSPACE}/fidl/src-gen/v1/hello_world/*.cpp")
list(SORT FIDL_SRCS_HELLOWORLD)

add_executable(GoodByeClient
	src/GoodByeClient.cpp
	${FIDL_SRCS_GOODBYE}
    ${FIDL_SRCS_HELLOWORLD}
	)
target_link_libraries(GoodByeClient CommonAPI CommonAPI-DBus dbus-1)

add_executable(GoodByeService
	src/GoodByeService.cpp
	src/GoodByeStubImpl.cpp
	${FIDL_SRCS_GOODBYE}
	)
target_link_libraries(GoodByeService CommonAPI CommonAPI-DBus dbus-1)
