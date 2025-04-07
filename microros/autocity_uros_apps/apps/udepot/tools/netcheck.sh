#!/bin/bash
###
 # @Author: hanson
 # @Date: 2024-12-02 10:48:20
 # @LastEditors: hanson
 # @LastEditTime: 2024-12-02 10:48:59
 # @Description:
 # @FilePath: \autocity_uros_apps\apps\udepot\tools\netcheck.sh
###

#检测网络链接畅通
function network()
{
    #超时时间
    local timeout=1

    #目标网站
    local target=www.baidu.com

    #获取响应状态码
    local ret_code=`curl -I -s --connect-timeout ${timeout} ${target} -w %{http_code} | tail -n1`

    if [ "x$ret_code" = "x200" ]; then
        #网络畅通
        return 1
    else
        #网络不畅通
        return 0
    fi

    return 0
}

LOGPATH=/autocity/data/netcheck.log

timestamps=`date`
echo "timestamp:"$timestamps >> $LOGPATH

check_count=0
retry_count=0

while true
do
    network
    if [ $? -eq 0 ];then
        if [ $check_count -gt 5 ];then
           fail="net disconnect,retry_count:"$retry_count
           echo $fail >> $LOGPATH
           echo "网络不畅通，重新拨号"
           pkill -9 quectel-CM
           sleep 3
           quectel-CM &
           sleep 10
           let check_count=0
           let retry_count=$retry_count+1
        fi
        let check_count=$check_count+1
        sleep 1
    else
        echo "网络畅通，你可以上网冲浪！"
        suc="net connect ok,retry_count:"$retry_count
        echo $suc >> $LOGPATH
        sleep 30
        let retry_count=0
        let check_count=0
    fi

done


exit 0
