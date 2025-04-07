#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-11-27 11:48:58
 # @LastEditors: hanson
 # @LastEditTime: 2024-11-27 14:57:25
 # @Description:
 # @FilePath: \autocity_uros_apps\apps\udepot\tools\autocity_setup\setup-app.sh
###

echo "4. setup water_station.service start"

sudo cp water_station.service /etc/systemd/system
sudo systemctl daemon-reload
sudo systemctl start water_station.service
sudo systemctl enable water_station.service

echo "setup water_station.service  done"
