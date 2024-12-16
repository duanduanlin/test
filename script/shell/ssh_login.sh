#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-12-02 10:48:20
 # @LastEditors: hanson
 # @LastEditTime: 2024-12-02 11:18:14
 # @Description:
 # @FilePath: \test\script\shell\ssh_login.sh
###


timestamps=`date`
echo "timestamp:"$timestamps

check_count=0

while true
do
    sshpass -p youyeetoo ssh youyeetoo@192.168.2.195 -p 9007 "ls"
    if [ $? -eq 0 ];then
        echo "check success check_count:"$check_count
        sshpass -p youyeetoo ssh youyeetoo@192.168.2.195 -p 9007 "echo youyeetoo | sudo -S reboot"
        sleep 300
        let check_count=$check_count+1
    else
        echo "check failed after:"$check_count
        break

    fi

done

echo "done"
exit 0
