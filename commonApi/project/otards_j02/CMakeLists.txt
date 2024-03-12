cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(hello_world_j02)
message(STATUS "Project name: ${PROJECT_NAME}")

set(J02WORKSPACE "/home/dding3/work/mpu/jbox02/jbox02")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wall -fno-exceptions -Wunused-variable -march=armv7-a -mfpu=neon -pipe -fomit-frame-pointer -fPIC -Werror=implicit-function-declaration -D_GNU_SOURCE -fdiagnostics-color=auto -g -DUSE_DEBUG=1 -fno-rtti -lpthread -lcurl -lssl -lcrypto -lz -lm -ldl")
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
    ${J02WORKSPACE}/4external/libota/include
    ${J02WORKSPACE}/middleware/modules/log/include
    ${J02WORKSPACE}/middleware/modules/platform/include
	)

link_directories(
  ${J02WORKSPACE}/external/sdk/ql_ec20/a07/ql-ol-extsdk/lib
  ${J02WORKSPACE}/platforms/ql_ec20/sdk/a07/prebuild/lib
 ${WORKSPACE}/3rdlibs/lib_j02
)

add_executable(otards_test
	src/main.cpp
	)
target_link_libraries(otards_test CommonAPI CommonAPI-DBus dbus-1 ota ipc middleware)
