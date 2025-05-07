cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(vSomeIpVbox)
message(STATUS "Project name: ${PROJECT_NAME}")

set(VBOXWORKSPACE "/home/dding3/work/mpu/vbox01/vbox01")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -mcpu=cortex-a53 -march=armv8-a+crc+crypto -fstack-protector-strong -Wformat -Wformat-security -Werror=format-security -mfloat-abi=hard --sysroot=${VBOXWORKSPACE}/external/sdk/ql_ag570/a11/ql-sysroots")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/output/apps/bin")
SET( CMAKE_CXX_COMPILER /opt/ql_crosstools/ql-ag550qcn-le20-gcc820-v1-toolchain/gcc/usr/bin/arm-oe-linux-gnueabi/arm-oe-linux-gnueabi-g++ )

#find_package (vsomeip3 3.3.8 REQUIRED)

include_directories(
	include
    ${VBOXWORKSPACE}/external/sdk/ql_ag570/a11/ql-sysroots/usr/include
    ${VBOXWORKSPACE}/platforms/ql_ag570/sdk/a11/prebuild/include
	)

link_directories(
  ${VBOXWORKSPACE}/external/sdk/ql_ag570/a11/ql-ol-rootfs/lib
  ${VBOXWORKSPACE}/platforms/ql_ag570/sdk/a11/prebuild/lib
)

add_executable(vSomeIpVboxClient
	src/someip_client.cpp
	)
target_link_libraries(vSomeIpVboxClient vsomeip3 vsomeip3-sd)

add_executable(vSomeIpVboxServer
	src/someip_server.cpp
	)
target_link_libraries(vSomeIpVboxServer vsomeip3 vsomeip3-sd)
