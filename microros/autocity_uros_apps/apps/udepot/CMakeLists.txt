# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)

set(COMPATIBLE_BOARDS disco_l475_iot1 olimex_stm32_e407 native_posix native_posix_64 nucleo_h743zi nucleo_f746zg blackpill_f411ce blackpill_f401ce)
if(NOT ${BOARD} IN_LIST COMPATIBLE_BOARDS)
    message(FATAL_ERROR "App $ENV{UROS_APP} not compatible with board ${BOARD}")
endif()

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(microrosapp C CXX)

set(microros_src_dir   ${MICRO_ROS_FIRMWARE_DIR}/autocity_uros_apps/microros_extensions)
set(microros_build_dir ${MICRO_ROS_FIRMWARE_DIR}/build/microros_extensions)

if(${MICRO_ROS_TRANSPORT} STREQUAL "serial")
    add_compile_definitions(MICRO_ROS_TRANSPORT_SERIAL)
elseif(${MICRO_ROS_TRANSPORT} STREQUAL "udp")
    add_compile_definitions(MICRO_ROS_TRANSPORT_UDP)
elseif(${MICRO_ROS_TRANSPORT} STREQUAL "serial-usb")
    add_compile_definitions(MICRO_ROS_TRANSPORT_SERIALUSB)
endif()

set(MICROROS_LIB_DIR     ${MICRO_ROS_FIRMWARE_DIR}/autocity_uros_apps/microroslib/lib)
set(MICROROS_INCLUDE_DIR ${MICRO_ROS_FIRMWARE_DIR}/autocity_uros_apps/microroslib/include)

set(NATIVE_LIB_DIR     ${MICRO_ROS_FIRMWARE_DIR}/autocity_uros_apps/native/)
set(3rd_LIB_DIR     ${MICRO_ROS_FIRMWARE_DIR}/autocity_uros_apps/3rdlibs)
set(COMMON_DIR     ${MICRO_ROS_FIRMWARE_DIR}/autocity_uros_apps/common)

FILE(GLOB
app_sources src/*.cpp
src/msg_wrap/*.cpp
src/transport/*.cpp
src/vehicle/*.cpp
src/vehicle/water_depot/*.cpp
src/vehicle/water_depot/protocol/*.cpp
src/vehicle/trash_depot/*.cpp
src/vehicle/trash_depot/protocol/*.cpp
src/trace/*.cpp
src/modbus/*.cpp
src/sensor/*.cpp
${COMMON_DIR}/src/trace/*.cpp
${microros_src_dir}/microros_transports.c)

include_directories(${microros_src_dir})

target_sources(app PRIVATE ${app_sources})

zephyr_get_include_directories_for_lang_as_string(       C includes)
zephyr_get_system_include_directories_for_lang_as_string(C system_includes)
zephyr_get_compile_definitions_for_lang_as_string(       C definitions)
zephyr_get_compile_options_for_lang_as_string(           C options)

zephyr_get_include_directories_for_lang_as_string(       CXX includes_cxx)
zephyr_get_system_include_directories_for_lang_as_string(CXX system_includes_cxx)
zephyr_get_compile_definitions_for_lang_as_string(       CXX definitions_cxx)
zephyr_get_compile_options_for_lang_as_string(           CXX options_cxx)

#zephyr_library_compile_options(-frtti)

if(CMAKE_GENERATOR STREQUAL "Unix Makefiles")
set(submake "$(MAKE)")
else()
set(submake "make")
endif()

include_directories(
    ${MICROROS_INCLUDE_DIR}
    ${MICROROS_INCLUDE_DIR}/action_msgs
    ${MICROROS_INCLUDE_DIR}/actionlib_msgs
    ${MICROROS_INCLUDE_DIR}/builtin_interfaces
    ${MICROROS_INCLUDE_DIR}/uchassis_msgs
    ${MICROROS_INCLUDE_DIR}/common_interfaces
    ${MICROROS_INCLUDE_DIR}/composition_interfaces
    ${MICROROS_INCLUDE_DIR}/ucontrol_msgs
    ${MICROROS_INCLUDE_DIR}/udepot_cmd_msgs
    ${MICROROS_INCLUDE_DIR}/udepot_status_msgs
    ${MICROROS_INCLUDE_DIR}/diagnostic_msgs
    ${MICROROS_INCLUDE_DIR}/example_interfaces
    ${MICROROS_INCLUDE_DIR}/geometry_msgs
    ${MICROROS_INCLUDE_DIR}/libyaml_vendor
    ${MICROROS_INCLUDE_DIR}/lifecycle_msgs
    ${MICROROS_INCLUDE_DIR}/micro_ros_msgs
    ${MICROROS_INCLUDE_DIR}/micro_ros_utilities
    ${MICROROS_INCLUDE_DIR}/microcdr
    ${MICROROS_INCLUDE_DIR}/microxrcedds_client
    ${MICROROS_INCLUDE_DIR}/nav_msgs
    ${MICROROS_INCLUDE_DIR}/rcl
    ${MICROROS_INCLUDE_DIR}/rcl_action
    ${MICROROS_INCLUDE_DIR}/rcl_interfaces
    ${MICROROS_INCLUDE_DIR}/rcl_lifecycle
    ${MICROROS_INCLUDE_DIR}/rcl_logging_interface
    ${MICROROS_INCLUDE_DIR}/rcl_logging_noop
    ${MICROROS_INCLUDE_DIR}/rclc
    ${MICROROS_INCLUDE_DIR}/rclc_lifecycle
    ${MICROROS_INCLUDE_DIR}/rclc_parameter
    ${MICROROS_INCLUDE_DIR}/rcutils
    ${MICROROS_INCLUDE_DIR}/rmw
    ${MICROROS_INCLUDE_DIR}/rmw_implementation
    ${MICROROS_INCLUDE_DIR}/rmw_implementation_cmake
    ${MICROROS_INCLUDE_DIR}/rmw_microxrcedds
    ${MICROROS_INCLUDE_DIR}/ros2trace
    ${MICROROS_INCLUDE_DIR}/rosgraph_msgs
    ${MICROROS_INCLUDE_DIR}/rosidl_adapter
    ${MICROROS_INCLUDE_DIR}/rosidl_cli
    ${MICROROS_INCLUDE_DIR}/rosidl_cmake
    ${MICROROS_INCLUDE_DIR}/rosidl_default_generators
    ${MICROROS_INCLUDE_DIR}/rosidl_default_runtime
    ${MICROROS_INCLUDE_DIR}/rosidl_generator_c
    ${MICROROS_INCLUDE_DIR}/rosidl_generator_cpp
    ${MICROROS_INCLUDE_DIR}/rosidl_generator_dds_idl
    ${MICROROS_INCLUDE_DIR}/rosidl_parser
    ${MICROROS_INCLUDE_DIR}/rosidl_runtime_c
    ${MICROROS_INCLUDE_DIR}/rosidl_runtime_cpp
    ${MICROROS_INCLUDE_DIR}/rosidl_typesupport_c
    ${MICROROS_INCLUDE_DIR}/rosidl_typesupport_cpp
    ${MICROROS_INCLUDE_DIR}/rosidl_typesupport_interface
    ${MICROROS_INCLUDE_DIR}/rosidl_typesupport_introspection_c
    ${MICROROS_INCLUDE_DIR}/rosidl_typesupport_introspection_tests
    ${MICROROS_INCLUDE_DIR}/rosidl_typesupport_microxrcedds_c
    ${MICROROS_INCLUDE_DIR}/rosidl_typesupport_microxrcedds_c_tests
    ${MICROROS_INCLUDE_DIR}/rosidl_typesupport_microxrcedds_cpp
    ${MICROROS_INCLUDE_DIR}/rosidl_typesupport_microxrcedds_cpp_tests
    ${MICROROS_INCLUDE_DIR}/rosidl_typesupport_microxrcedds_test_msg
    ${MICROROS_INCLUDE_DIR}/sensor_msgs
    ${MICROROS_INCLUDE_DIR}/sensor_msgs_py
    ${MICROROS_INCLUDE_DIR}/shape_msgs
    ${MICROROS_INCLUDE_DIR}/statistics_msgs
    ${MICROROS_INCLUDE_DIR}/std_msgs
    ${MICROROS_INCLUDE_DIR}/std_srvs
    ${MICROROS_INCLUDE_DIR}/stereo_msgs
    ${MICROROS_INCLUDE_DIR}/test_interface_files
    ${MICROROS_INCLUDE_DIR}/test_msgs
    ${MICROROS_INCLUDE_DIR}/test_rmw_implementation
    ${MICROROS_INCLUDE_DIR}/test_tracetools
    ${MICROROS_INCLUDE_DIR}/test_tracetools_launch
    ${MICROROS_INCLUDE_DIR}/tracetools
    ${MICROROS_INCLUDE_DIR}/tracetools_launch
    ${MICROROS_INCLUDE_DIR}/tracetools_read
    ${MICROROS_INCLUDE_DIR}/tracetools_test
    ${MICROROS_INCLUDE_DIR}/tracetools_trace
    ${MICROROS_INCLUDE_DIR}/trajectory_msgs
    ${MICROROS_INCLUDE_DIR}/unique_identifier_msgs
    ${MICROROS_INCLUDE_DIR}/visualization_msgs
    ${NATIVE_LIB_DIR}/socket_can/include
    ${NATIVE_LIB_DIR}/ufile/include
    ${NATIVE_LIB_DIR}/backtrace/include
    ${NATIVE_LIB_DIR}/ringbuffer/include
    ${NATIVE_LIB_DIR}/flow_sensor/include
    ${NATIVE_LIB_DIR}/uart/include
    ${NATIVE_LIB_DIR}/modbus/include
    ${3rd_LIB_DIR}/include
    ${COMMON_DIR}/include
    include
    )

#link_directories(
#  ${CANCARD_LIB_DIR}
#)
if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
    message("this is aarch64 cpu")
    target_link_libraries(app PUBLIC ${MICROROS_LIB_DIR}/libmicroros-aarch64.a ${NATIVE_LIB_DIR}/libnative-aarch64.a ${3rd_LIB_DIR}/lib/libmodbus_aarch64.a)
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
	message("this is x86_64 cpu")
    target_link_libraries(app PUBLIC ${MICROROS_LIB_DIR}/libmicroros-x86_64.a ${NATIVE_LIB_DIR}/libnative-x86_64.a ${3rd_LIB_DIR}/lib/libmodbus_x86_64.a)
endif()
