'''
Author: hanson
Date: 2024-12-24 10:42:31
LastEditors: hanson
LastEditTime: 2024-12-24 15:53:03
Description:
FilePath: \test\ros2\src\system_analysis\system_analysis\system_analysis.py
'''

import time
import rclpy
from rclpy.node import Node
from disk_analysis import DiskAnalysis
from process_analysis import PorcessAnalysis
from memory_analysis import MemoryAnalysis

class SystemAnalysis(Node):
    def __init__(self):
        super().__init__('system_analysis')
        self.disk_analysis = DiskAnalysis("sda")
        self.process_analysis = PorcessAnalysis()
        self.memory_analysis = MemoryAnalysis()
        self.interval=1

    def loop_run(self):
        while True:
            # 1.监控SOC系统cpu,mem,disk
            print("analysis system cpu,mem.disk,io\r\n");
            read_rate, write_rate = self.disk_analysis.get_disk_io_rate(self.interval)
            print(f"Read rate: {read_rate:.2f} MB/s, Write rate: {write_rate:.2f} MB/s")
            #process
            process_attr = self.process_analysis.get_process_attr("system_analysis")
            print(process_attr)
            self.process_analysis.update_csv_record(process_attr)
            #memory
            memory_attr = self.memory_analysis.get_mem_attr()
            print(memory_attr)
            time.sleep(self.interval)

def main(args=None):
    rclpy.init(args=args)
    system_analysis = SystemAnalysis()
    system_analysis.loop_run()


if __name__ == '__main__':
    main()
