#!/bin/bash
set -x

if [ $# -ne 1 ];then
    echo "请输入端口"
    exit 1
fi
port=$1
sed -i "s/xxxx/${port}/g" frpc.ini

sudo mkdir -p /etc/frp
sudo cp -rf frpc frpc.ini /etc/frp
sudo cp frpc.service /etc/systemd/system
sudo systemctl daemon-reload
sudo systemctl restart frpc
sudo systemctl enable frpc

cat /etc/frp/frpc.ini
ps -ef|grep frpc