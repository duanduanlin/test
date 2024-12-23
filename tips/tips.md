<!--
 * @Author: dding3 dding3@jmc.com.cn
 * @Date: 2024-03-14 19:38:12
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-17 13:40:08
 * @FilePath: \test\tips\tips.md
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
-->
# 常用指令
## 修改selinux下文件type
chcon -t var_t /var/www/html/index.html
## 启动dbus-deamon
dbus-daemon --fork --session --address=unix:path=/tmp/dbus-o6ujiqBKsY
export DBUS_SESSION_BUS_ADDRESS=unix:path=/tmp/dbus-o6ujiqBKsY
## 设置链接库路径
export LD_LIBRARY_PATH=/oemdata/apps:/oemdata:/APP:/lib:/usr/lib
## MD5计算
md5sum xxx
## dos格式转换
dos2unix install.sh
## unzip 解压
unzip ohmyzsh-master.zip
## find指令
find . -name mcu_pipe
## 查看分区
df -h
du -sh
## 查看cpu占有率
top
## 查看内存信息
cat /proc/meminfo
## 查看系统信息
uname -a
## 查看目录大小
du -lh --max-depth=1
## grep
grep -r "ql_log_print" ./
## 查看依赖关系
readelf -d xxx.so | grep NEEDED
## nm 查看符号信息
nm -D  external/ql_ec20/ql-ol-extsdk/lib/libql_peripheral.so | grep ql_log_print
## 生成patch和打patch
diff -u ori.c tar.c > update.patch
patch ori.c < update.patch
## 清除内存缓存
echo 3 > /proc/sys/vm/drop_caches
## 文件切割
split -d -l 100000 -a 8 ConEmu-2023-06-21-p9656.log
## 软链接
ln -s libCommonAPI-DBus.so.3.1.12 libCommonAPI-DBus.so.3
## 查看库依赖
objdump -x test| grep NEED
## 堆栈分析
addr2line -e /autocity/rdcu/install/ucanbus/zephyr.elf 0x17102
## 内存泄露
valgrind --show-reachable=yes --show-leak-kinds=all --undef-value-errors=no --log-file=valgrind.log /autocity/rdcu/install/ucanbus/scripts/start.sh
## 查看串口引脚配置
cat sys/kernel/debug/pinctrl/1000000.pinctrl/pinmux-pins
ls /sys/devices/78b3000.serial/tty/
## 查看linux版本
uname -a
## 抓包
tcpdump -i ccinet1 tcp port 9315 and host 10.15.2.58 -w ./tsp.pcap
sudo tcpdump udp -i lo port 8888
## git
git config --global user.email "hanson@citygo.com.cn"
git config --global user.name "hanson"
git submodule update --init --recursive
## git diff生成patch
git diff ./ > test.patch //生成patch
patch -p1 < test.patch //打patch
git apply test.patch //也可用这个命令打patch
## 安装模拟器
sudo apt-get install qemu-user-static binfmt-support qemu
sudo update-binfmts --enable qemu-x86_64
## docker相关
sudo docker commit  b4293c3b9202  mask_detectionv2:v2
docker save -o mask_detection_v5.tar mask_detection:v5
sudo docker load -i mask_detection_v5.tar

docker run --privileged --network host -v /dev:/dev -it micros-linux-aarch64:v0814 /bin/bash
docker pull 192.168.2.195:7443/v2/humble-x86:v0704
docker exec -it d500218a8f5d bash

docker run -v /home/hanson/:/home/host/hanson/ -it --rm 192.168.2.195:7443/v2/humble-x86:v0704
docker run  -v /home/hanson/:/home/host/hanson/ --name=humble-aarch64 --platform linux/arm64 -it --rm b4f1ffd83abe

docker login 192.168.2.195:7443
docker pull 192.168.2.195:7443/v2/isaac_ros_dev-cross_compiler:v1.3
docker tag 192.168.2.195:7443/v2/isaac_ros_dev-cross_compiler:v1.3 isaac_ros_dev-cross_compiler:v1.3
docker images

## 安装
sudo apt-get update

sudo apt-get install apt-transport-https ca-certificates curl software-properties-common

curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -

sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"

sudo apt-get update

sudo apt-get install docker-ce docker-ce-cli containerd.io

sudo usermod -aG docker $USER

sudo systemctl start docker

newgrp docker

## python虚拟环境
sudo apt install python3-venv
python3 -m venv ~/zephyrproject/.venv
source ~/zephyrproject/.venv/bin/activate
## socket can 调试
ip link set can0 down
ip link set can0 up
ip -details link show can0
cansend can0 123#000102030405060708

sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

sudo ip link del dev vcan0
sudo apt install can-utils

## scp
scp -r install/aarch64/canbus autocity@192.168.6.137:/autocity/sweeper/
scp -P 7015 micros-linux-aarch64_v0905.tar ubuntu@192.168.2.195:/autocity/rdcu

## ros
ros2 pkg create --build-type ament_cmake --node-name my_node my_package
colcon build --packages-select my_package
ros2 topic pub --once /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}"
ros2 topic pub --rate 1 /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.8}}"
ros2 service call /spawn turtlesim/srv/Spawn "{x: 2, y: 2, theta: 0.2, name: ''}"
ros2 action info /turtle1/rotate_absolute
ros2 action send_goal /turtle1/rotate_absolute turtlesim/action/RotateAbsolute "{theta: 1.57}"
ros2 topic info --verbose /ucanbus/chassis

## 启动时间
last -x reboot | head -1
last -x shutdown | head -1
uptime -p
systemd-analyze blame
systemd-analyze time
