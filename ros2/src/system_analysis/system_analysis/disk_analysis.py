'''
Author: hanson
Date: 2024-12-24 11:33:42
LastEditors: hanson
LastEditTime: 2024-12-24 11:39:36
Description:
FilePath: \test\ros2\src\system_analysis\system_analysis\disk_analysis.py
'''
class DiskAnalysis:
    def __init__(self, device_name):
        self.device_name = device_name
        self.device_file = f"/sys/block/{device_name}/stat"
        self.last_stat = self.get_io_stats()

    def get_io_stats(self):
        device_file = self.device_file
        with open(device_file, "r") as f:
            stats = f.read().split()
            read_ios = int(stats[0])
            write_ios = int(stats[4])
            read_sectors = int(stats[2])
            write_sectors = int(stats[6])
            return read_ios, write_ios, read_sectors, write_sectors

    def get_disk_io_rate(self, interval=1):
        device_file = self.device_file
        read_ios_start, write_ios_start, read_sectors_start, write_sectors_start = self.last_stat
        read_ios_end, write_ios_end, read_sectors_end, write_sectors_end = cur_stat = self.get_io_stats()

        read_bytes = (read_sectors_end - read_sectors_start) * 512
        write_bytes = (write_sectors_end - write_sectors_start) * 512

        read_rate = (read_bytes / (1024 * 1024)) / interval
        write_rate = (write_bytes / (1024 * 1024)) / interval

        self.last_stat = cur_stat

        return read_rate, write_rate
