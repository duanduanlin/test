#! /bin/bash
###
 # @Author: hanson
 # @Date: 2024-08-08 14:46:33
 # @LastEditors: hanson
 # @LastEditTime: 2024-09-18 15:48:36
 # @Description:
 # @FilePath: \autocity_uros_setup\scripts\make_run_package.sh
###

set -e
set -o nounset
set -o pipefail

FW_TARGETDIR=$(pwd)/firmware
PREFIX=$(ros2 pkg prefix autocity_uros_setup)

# Checking if firmware exists
if [ -d $FW_TARGETDIR ]; then
    RTOS=$(head -n1 $FW_TARGETDIR/PLATFORM)
    PLATFORM=$(head -n2 $FW_TARGETDIR/PLATFORM | tail -n1)
else
    echo "Firmware folder not found. Please use ros2 run autocity_uros_setup create_firmware_ws.sh to create a new project."
    exit 1
fi

# Flash specific firmware folder if needed
if [ -d "$PREFIX/config/$RTOS/generic" ]; then
    if [ -f $PREFIX/config/$RTOS/generic/make_run.sh ]; then
      echo "make run package for $RTOS platform $PLATFORM"
      . $PREFIX/config/$RTOS/generic/make_run.sh
    else
      echo "No run step found for $RTOS platform $PLATFORM"
    fi
else
    if [ -f $PREFIX/config/$RTOS/$PLATFORM/make_run.sh ]; then
      echo "make run package for $RTOS platform $PLATFORM"
      . $PREFIX/config/$RTOS/$PLATFORM/make_run.sh
    else
      echo "No run step found for $RTOS platform $PLATFORM"
    fi
fi
