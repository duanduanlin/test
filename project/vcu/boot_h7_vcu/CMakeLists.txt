# cmake version
cmake_minimum_required (VERSION 3.0.0)

# set mcu type
set(MCU_PLATFORM cortex-m7)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# compiler type
set(CMAKE_BUILD_TYPE debug)

if(CMAKE_BUILD_TYPE MATCHES debug)
  message("debug build.")
elseif(CMAKE_BUILD_TYPE MATCHES release)
  message("release build.")
endif()

#define global variable
set_property(GLOBAL PROPERTY STATIC_LIBS_SRC)

# set search path for cmake modules-arm_toolchain.cmake
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/arm_toolchain.cmake)

# set project
set(app_name "VCU_BOOT")
project(${app_name} C CXX ASM)

# set some project constants
set(elf_file ${app_name}.elf)
set(bin_file ${app_name}.bin)
set(hex_file ${app_name}.hex)
set(map_file ${app_name}.map)
set(lss_file ${app_name}.lss)

# set output path
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# project macro define
add_definitions("-DSTM32H743xx")
add_definitions("-DUSE_HAL_DRIVER")

# project include file
set(HEADER_FILE_DIR
  boot_component
  board
  board/hal/Core/Inc
  board/hal/fwlib/CMSIS/Include
  board/hal/fwlib/STM32H7xx_HAL_Driver/Inc
  board/hal/fwlib/CMSIS/Device/ST/STM32H7xx/Include
  modules/easylogger/easylogger/inc
  modules/easylogger/port
  modules/uavcan/canard/libcanard
  modules/uavcan/port
  modules/uavcan/port/source
  modules/segger_rtt
  packages/ringbuffer
  # packages/crc
  packages/o1heap/o1heap
)
include_directories(${HEADER_FILE_DIR})

# linker script
get_filename_component(LINKER_SCRIPT board/linker_scripts/link.ld ABSOLUTE)
message(${LINKER_SCRIPT})

# add lib and src files
include(module)
set(MODULES_SRC_DIRS
  board/hal
  board
  modules
  packages
  boot_component
  # examples
)
add_module(${MODULES_SRC_DIRS})

# add depende

# generate the target
get_property(sources_file GLOBAL PROPERTY SOURCES_FILE)
# message(${sources_file})
# message(${SOURCE_FILE})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${map_file} -T${LINKER_SCRIPT}")

# add sources to elf file
add_executable(${elf_file} ${sources_file})

# link StdPeriph library to project
get_property(SOURCE_LIBS GLOBAL PROPERTY STATIC_LIBS_SRC)
target_link_libraries(${elf_file} PUBLIC ${SOURCE_LIBS})

# link with linker file
# target_link_libraries(${elf_file} PUBLIC -T${LINKER_SCRIPT})

# show size of resulting firmware image
add_custom_target(${elf_file}-size DEPENDS ${elf_file} COMMAND ${ARM_SIZE_EXECUTABLE} -B ${elf_file})

# generate extended listing
add_custom_target(${lss_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJDUMP_EXECUTABLE} -S ${elf_file} > ${lss_file})

# create binary and hex files
add_custom_target(${hex_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJCOPY_EXECUTABLE} -Oihex ${elf_file} ${hex_file})
add_custom_target(${bin_file} DEPENDS ${elf_file} COMMAND ${ARM_OBJCOPY_EXECUTABLE} -Obinary ${elf_file} ${bin_file})
add_custom_target(${map_file} DEPENDS ${elf_file} -Wl -Map ${elf_file} ${map_file})
add_custom_target(${app_name} ALL DEPENDS ${elf_file}-size ${bin_file} ${hex_file} ${lss_file})

add_custom_target(clean-all COMMAND rm -rf ${CMAKE_BINARY_DIR}/*)

# execute_process(COMMAND sh ../test.sh)
