'''
Author: hanson
Date: 2024-12-24 14:06:58
LastEditors: hanson
LastEditTime: 2024-12-24 14:24:15
Description:
FilePath: \test\ros2\src\system_analysis\system_analysis\process_analysis.py
'''

import os
import time
# import copy
# import csv
# from dataclasses import dataclass, field
import psutil

ProcessIter=[
        "pid",
        "name",
        "cpu_percent",
        "memory_percent",
        "memory_info",
        "status",
        "create_time",
        "cpu_times",
        "num_ctx_switches",
        "open_files",
        "num_threads",
    ]

class PorcessAnalysis:

    # def __init__(self):

    # def __del__(self):
        # try:
        #     if self.csv_fp:
        #         self.release_csv()
        # except Exception:
        #     print("not csv file")

    def get_process_data(self):
        self.process_list = []
        cur_time = time.time()
        all_process_info = psutil.process_iter(ProcessIter)
        for proc in all_process_info:
            print(proc.info)
