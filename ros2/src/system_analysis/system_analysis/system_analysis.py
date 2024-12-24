'''
Author: hanson
Date: 2024-12-24 10:42:31
LastEditors: hanson
LastEditTime: 2024-12-24 10:58:58
Description:
FilePath: \test\ros2\src\system_analysis\system_analysis\system_analysis.py
'''
import time
import rclpy
from rclpy.node import Node

class System_Analysis(Node):
    def __init__(self):
        super().__init__('system_analysis')

    def loop_run(self):
        while True:
            # 1.监控SOC系统cpu,mem,disk
            print("analysis system cpu,mem.disk,io\r\n");
            time.sleep(1)

def main(args=None):
    rclpy.init(args=args)
    system_analysis = System_Analysis()
    system_analysis.loop_run()


if __name__ == '__main__':
    main()
