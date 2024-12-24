'''
Author: hanson
Date: 2024-12-24 10:42:31
LastEditors: hanson
LastEditTime: 2024-12-24 15:20:58
Description:
FilePath: \test\ros2\src\system_analysis\system_analysis\system_analysis.py
'''
import os
import time
import csv
import rclpy
from rclpy.node import Node
from disk_analysis import DiskAnalysis
from process_analysis import PorcessAnalysis

CSV_FIELD= [
    "time",
    "name",
    "pid",
    "cpu_percent",
    "mem_percent",
    "mem_used",
    "io_read",
    "io_write",
    "read_Bytes",
    "write_Bytes",
    "uptime",
    "status",
    "cpu_times",
    "ctxt_switches",
    "no_ctxt_switches",
    "cswch",
    "nvcswch",
    "open_files",
    "num_threads",
]

CSV_FILE="/home/hanson/workspace/test/test/ros2/system_analysis.csv"

class SystemAnalysis(Node):
    def __init__(self):
        super().__init__('system_analysis')
        self.disk_analysis = DiskAnalysis("sda")
        self.process_analysis = PorcessAnalysis()
        self.interval=1
        self.init_csv()

    def __del__(self):
        try:
            if self.csv_fp:
                self.release_csv()
        except Exception:
            print("not csv file")

    def loop_run(self):
        while True:
            # 1.监控SOC系统cpu,mem,disk
            print("analysis system cpu,mem.disk,io\r\n");
            read_rate, write_rate = self.disk_analysis.get_disk_io_rate(self.interval)
            print(f"Read rate: {read_rate:.2f} MB/s, Write rate: {write_rate:.2f} MB/s")
            attr = self.process_analysis.get_process_attr("system_analysis")
            print(attr)
            self.update_csv_record(attr)
            time.sleep(self.interval)

    def init_csv(self):
        dirname = os.path.dirname(CSV_FILE)
        if not os.path.exists(dirname):
            os.system(f"mkdir -p {dirname}")
        self.csv_fp = open(CSV_FILE, "w", newline="")
        self.csv_writer = csv.DictWriter(
            self.csv_fp, fieldnames=CSV_FIELD
        )
        self.csv_writer.writeheader()

    def release_csv(self):
        self.csv_fp.close()

    def update_csv_record(self, data, csv_writer=None):
        if not csv_writer:
            csv_writer = self.csv_writer

        csv_data = {
            "time": data.time_stamp,
            "name": data.process_name,
            "pid": data.pid,
            "cpu_percent": data.cpu_percent,
            "mem_percent": data.mem_percent,
            "mem_used": data.mem_used,
            "io_read": data.io_read,
            "io_write": data.io_write,

            "read_Bytes": data.read_bytes,
            "write_Bytes": data.write_bytes,
            "uptime": data.uptime,
            "status": data.status,
            "cpu_times": data.cpu_times,
            "ctxt_switches": data.ctxt_switches,
            "no_ctxt_switches": data.no_ctxt_switches,
            "cswch": data.cswch,
            "nvcswch": data.nvcswch,
            "open_files": data.open_files,
            "num_threads": data.num_threads,
        }
        csv_writer.writerow(csv_data)

def main(args=None):
    rclpy.init(args=args)
    system_analysis = SystemAnalysis()
    system_analysis.loop_run()


if __name__ == '__main__':
    main()
