# autocity_uros_setup

Make modifications based on official procedures to fit company software。

base source:https://github.com/micro-ROS/micro_ros_setup.git

# 执行配置脚本
./src/autocity_uros_setup/tools/setup.sh

```
# Source the ROS 2 installation
source /opt/ros/$ROS_DISTRO/setup.bash

# Update dependencies using rosdep
sudo apt update && rosdep update
rosdep install --from-paths src --ignore-src -y

# Install pip
sudo apt-get install python3-pip

#build
colcon build

source install/setup.bash
#create agent
ros2 run autocity_uros_setup create_agent_ws.sh

#build agent
ros2 run autocity_uros_setup build_agent.sh
```
# 创建zephyr工作空间

git config --global http.postBuffer 5048576000

source install/setup.zsh

ros2 run autocity_uros_setup create_firmware_ws.sh zephyr host

pip install docutils==0.16

# 配置并编译测试软件
```
#配置软件
ros2 run autocity_uros_setup configure_firmware.sh ding_dang --transport udp --ip 127.0.0.1 --port 8888

#编译zepher程序
ros2 run autocity_uros_setup build_firmware.sh
```
# 运行agent
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
