<!--
 * @Author: dding3 dding3@jmc.com.cn
 * @Date: 2024-05-20 19:00:13
 * @LastEditors: dding3 dding3@jmc.com.cn
 * @LastEditTime: 2024-05-20 22:49:03
 * @FilePath: /test/ros/readme.md
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
-->
# 文档
https://blog.csdn.net/qq_25267657/article/details/84316111
# 安装
https://wiki.ros.org/cn/ROS/Installation
# 教程
https://wiki.ros.org/cn/ROS/Tutorials
# 使用
## 创建工作空间
mkdir -p ./catkin_ws/src 
cd catkin_ws
catkin_make
## 设置工作空间环境
source devel/setup.zsh
## 查找软件包
rospack find roscpp
## 切换软件包位置
roscd roscpp
## 查看软件包路径
echo $ROS_PACKAGE_PATH
## 切换ros日志目录
roscd log
## 显示软件包内容
rosls roscpp_tutorials
## 创建软件包
catkin_create_pkg beginner_tutorials std_msgs rospy roscpp
## 查看软件包依赖
- 直接依赖
rospack depends1 beginner_tutorials 
- 间接依赖
rospack depends beginner_tutorials 
## 编译
- catkin_make
- catkin_make --source my_src