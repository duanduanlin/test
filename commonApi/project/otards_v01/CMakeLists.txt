cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(hello_world_v01)
message(STATUS "Project name: ${PROJECT_NAME}")

set(VBOXWORKSPACE "/home/dding3/work/mpu/vbox01/vbox01")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -mcpu=cortex-a53 -march=armv8-a+crc+crypto -fstack-protector-strong -Wformat -Wformat-security -Werror=format-security -mfloat-abi=hard -g --sysroot=${VBOXWORKSPACE}/external/sdk/ql_ag570/a11/ql-sysroots")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/output/apps/bin")
SET( CMAKE_CXX_COMPILER /opt/ql_crosstools/ql-ag550qcn-le20-gcc820-v1-toolchain/gcc/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-g++ )

include_directories(
	include
	${WORKSPACE}/fidl/src-gen/
	${WORKSPACE}/3rdlibs/capicxx-core-runtime/include
	${WORKSPACE}/3rdlibs/capicxx-dbus-runtime/include
	${WORKSPACE}/3rdlibs/dbus-1.10.10
    ${VBOXWORKSPACE}/4external/libota/include
    ${VBOXWORKSPACE}/middleware/modules/log/include
    ${VBOXWORKSPACE}/middleware/modules/platform/include
    ${VBOXWORKSPACE}/external/sdk/ql_ag570/a11/ql-sysroots/usr/include
	)

link_directories(
  ${VBOXWORKSPACE}/external/sdk/ql_ag570/a11/ql-ol-extsdk/lib
  ${VBOXWORKSPACE}/platforms/ql_ag570/sdk/a11/prebuild/lib
 ${WORKSPACE}/3rdlibs/lib_v01
)

add_executable(otards_test_v01
	src/main.cpp
	)
target_link_libraries(otards_test_v01 CommonAPI CommonAPI-DBus dbus-1 ota ipc middleware)
