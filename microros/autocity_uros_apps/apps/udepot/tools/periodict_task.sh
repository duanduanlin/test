#!/bin/bash

# Scan folder to delete the old dirs or files
function scan_folder()
{
    # INFO:先删除文件, 再删除空目录
    scan_dir=$1
    # echo "超过1天的文件-------"
    # find $scan_dir -type f -mtime +1 -print
    # echo "超过1天的空目录+++++++"
    # find $scan_dir -type d -mtime +1 -print

    # find $scan_dir -type f -mtime +1 -exec rm -rf {} \;
    # find $scan_dir -type d -mtime +1 -exec rm -rf {} \;
    # find $scan_dir -type l -mtime +1 -exec rm -rf {} \;
    find $scan_dir -mtime +1 -type l,d,f -print -exec rm -rf {} \; | tee -a /autocity/data/logs/latest/clear_log_service/periodict_task.log
    # find $scan_dir -mtime +1 -exec rm -rf {} \;
}

function log_clean_task()
{
    echo "`date +"%Y-%m-%d_%H.%M.%S"` log clean task"
    LOGS=/autocity/data/logs
    JPEG=/autocity/sweeper/camera/camera_data/jpeg
    VIDEO=/autocity/sweeper/camera/camera_data/video

    scan_folder ${LOGS}
    scan_folder ${JPEG}
    scan_folder ${VIDEO}
}

function main_task()
{
    cpulimit -f -l 3 -c 1 --  nice -n 10 python3 /autocity/scripts/python_remove_log.py
    #log_clean_task
}

main_task
