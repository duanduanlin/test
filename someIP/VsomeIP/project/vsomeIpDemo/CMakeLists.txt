cmake_minimum_required(VERSION 2.8)

#项目名
PROJECT(vSomeIpDemo)
message(STATUS "Project name: ${PROJECT_NAME}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -pthread -std=c++0x")
#设置输出路径
SET( WORKSPACE "${CMAKE_CURRENT_SOURCE_DIR}/../../")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${WORKSPACE}/output/apps/bin")

find_package (vsomeip3 3.3.8 REQUIRED)

include_directories(
	include
    ${VSOMEIP3_INCLUDE_DIRS}
	)

add_executable(vSomeIpDemoClient
	src/someip_client.cpp
	)
target_link_libraries(vSomeIpDemoClient vsomeip3 vsomeip3-sd)

add_executable(vSomeIpDemoServer
	src/someip_server.cpp
	)
target_link_libraries(vSomeIpDemoServer vsomeip3 vsomeip3-sd)
