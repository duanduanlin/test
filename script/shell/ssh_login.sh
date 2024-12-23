#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-12-02 10:48:20
 # @LastEditors: hanson
 # @LastEditTime: 2024-12-23 10:53:32
 # @Description:
 # @FilePath: \test\script\shell\ssh_login.sh
###


check_count=0
try_count=0

while true
do
    timestamps=`date`
    echo "timestamp:"$timestamps
    sshpass -p youyeetoo ssh youyeetoo@192.168.2.195 -p 9007 "ls"
    if [ $? -eq 0 ];then
        echo "check success check_count:"$check_count
        sshpass -p youyeetoo ssh youyeetoo@192.168.2.195 -p 9007 "echo youyeetoo | sudo -S reboot"
        sleep 300
        let check_count=$check_count+1
        let try_count=0
    else
        if [ $try_count -gt 3 ];then
            echo "check failed after:"$check_count
            break
        else
            echo "check failed will try again,try_count:"$try_count
            let try_count=$try_count+1
            sleep 10
        fi
    fi

done

echo "done"
exit 0
