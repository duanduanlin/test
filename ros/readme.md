<!--
 * @Author: dding3 dding3@jmc.com.cn
 * @Date: 2024-05-20 19:00:13
 * @LastEditors: dding3 dding3@jmc.com.cn
 * @LastEditTime: 2024-05-21 19:34:13
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
## 运行主节点
roscore
## 查看运行中的节点
rosnode list
## 查看指定节点信息
rosnode info /rosout
## 运行指定节点
rosrun turtlesim turtlesim_node
## 测试节点是否正常
rosnode ping my_turtle
## 查看主题命令
rostopic -h
## 显示某个话题上的数据
rostopic echo /turtle1/command_velocity
## 列出当前的话题
rostopic list
## 查看某话题的消息类型
rostopic type rosout_agg
## 查看消息详细类型
rosmsg show rosgraph_msgs/Log
## 发布一条消息
rostopic pub -1 /turtle1/cmd_vel geometry_msgs/Twist -- '[2.0, 0.0, 0.0]' '[0.0, 0.0, 1.8]'
## 查看发布频率
rostopic hz rosout_agg
## 以图表的形式统计数据
rosrun rqt_plot rqt_plot
## 列出活跃服务
rosservice list
## 查看服务类型
rosservice type /clear
## 查看服务详细信息
rosservice type /spawn | rossrv show
## 调用服务
rosservice call /clear
## 显示参数
rosparam list
## 打开日志终端
rosrun rqt_console rqt_console
## 启动管理
roslaunch beginner_tutorials turtlemimic.launch
## 包编辑器
rosed roscpp Logger.msg