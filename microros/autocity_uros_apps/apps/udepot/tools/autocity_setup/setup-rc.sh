#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-11-27 11:48:58
 # @LastEditors: hanson
 # @LastEditTime: 2024-11-27 13:55:50
 # @Description:
 # @FilePath: \autocity_uros_apps\apps\udepot\tools\autocity_setup\setup-rc.sh
###

echo "3. setup rc.local start"

sudo cp rc.local /etc/
sudo chmod +x /etc/rc.local
sudo systemctl daemon-reload
sudo systemctl restart rc-local.service
sudo systemctl enable rc-local.service

echo "setup rc.local  done"
