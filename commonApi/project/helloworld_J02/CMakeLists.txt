cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(hello_world_j02)
message(STATUS "Project name: ${PROJECT_NAME}")

set(J02WORKSPACE "/home/dding3/work/mpu/jbox02/jbox02")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -std=c++0x")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/output/apps/bin")
SET( CMAKE_CXX_COMPILER ${J02WORKSPACE}/external/sdk/ql_ec20/a07/ql-ol-crosstool/sysroots/x86_64-oesdk-linux/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-g++ )

include_directories(
	include
	${WORKSPACE}/fidl/src-gen/
	${WORKSPACE}/3rdlibs/capicxx-core-runtime/include
	${WORKSPACE}/3rdlibs/capicxx-dbus-runtime/include
	${WORKSPACE}/3rdlibs/dbus-1.10.10
	)

link_directories(
  ${J02WORKSPACE}/external/sdk/ql_ec20/a07/ql-ol-extsdk/lib
  ${J02WORKSPACE}/platforms/ql_ec20/sdk/a07/prebuild/lib
)

add_executable(HelloMainJ0201
	src/HelloMain.cpp
	)
target_link_libraries(HelloMainJ0201 CommonAPI CommonAPI-DBus dbus-1)

add_executable(HelloMainJ0202
	src/HelloMain.cpp
	)
target_link_libraries(HelloMainJ0202)

add_executable(HelloMainJ02RPC
	src/HelloMainRPC.cpp
	)
target_link_libraries(HelloMainJ02RPC CommonAPI CommonAPI-DBus dbus-1)

add_executable(HelloWorldClientJ02
	src/HelloWorldClient.cpp
	${FIDL_SRCS_HELLOWORLD}
	)
target_link_libraries(HelloWorldClientJ02 CommonAPI CommonAPI-DBus dbus-1)

add_executable(HelloWorldServiceJ02
	src/HelloWorldService.cpp
	src/HelloWorldStubImpl.cpp
	${FIDL_SRCS_HELLOWORLD}
	)
target_link_libraries(HelloWorldServiceJ02 CommonAPI CommonAPI-DBus dbus-1)
