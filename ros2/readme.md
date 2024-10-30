#ros2测试
## 包创建
ros2 pkg create --build-type ament_cmake --node-name my_node my_package（带节点的包）
ros2 pkg create --build-type ament_python py_pubsub（空包不带节点）
ros2 pkg create --build-type ament_cmake cpp_srvcli --dependencies rclcpp example_interfaces（自动添加依赖）
ros2 pkg create --build-type ament_cmake --dependencies pluginlib --node-name area_node --license Apache-2.0 polygon_base （带license）
ros2 pkg create --build-type ament_cmake --dependencies polygon_base pluginlib --library-name polygon_plugins --license Apache-2.0 polygon_plugins
## 编译运行
- 编译：colcon build
- 指定编译：colcon build --packages-select cpp_pubsub
- 设置环境变量：source install/local_setup.zsh
- 运行：ros2 run my_package my_node
- 僵尸进程：ps -ef | grep defunct | more
## 启动
- ros2 launch cpp_parameters cpp_parameters_launch.py
##  包依赖检查
rosdep install -i --from-path src --rosdistro humble -y
## 命令行调试
- 发布主题:ros2 topic pub /topic std_msgs/msg/String "data: Hello world"
- 检测：ros2 topic echo /topic
