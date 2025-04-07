#!/bin/bash
/autocity/sweeper/udepot/scripts/start.sh&

source /autocity/sweeper/setup.bash
cd /autocity/scripts
ros2 launch water_station water_station_launch.py
