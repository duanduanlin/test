'''
Author: hanson
Date: 2024-12-24 14:06:58
LastEditors: hanson
LastEditTime: 2024-12-24 15:10:35
Description:
FilePath: \test\ros2\src\system_analysis\system_analysis\process_analysis.py
'''

import time
# import copy
from dataclasses import dataclass, field
import psutil

@dataclass
class Process_Attr:
    process_name: str
    time: float = 0
    time_stamp: str = ""
    pid: int = 0
    cpu_percent: float = 0
    mem_percent: float = 0
    mem_used: float = 0
    last_time: float = 0.0
    last_io = None
    last_io_time = 0
    io_read: float = 0
    io_write: float = 0
    read_bytes: int = 0
    write_bytes: int = 0
    uptime: int = 0
    status: str = ""
    cpu_times: str = ""
    running_stat: bool = False
    ctxt_switches: int = 0
    no_ctxt_switches: int = 0
    cswch: int = 0
    nvcswch: int = 0
    open_files: int = 0
    num_threads: int = 0

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

    def statistic_ctx_switches(self, proc, attr, cur_time):
        # now_time = time.time()
        ctx = proc.num_ctx_switches()
        if attr.ctxt_switches == 0:
            attr.ctxt_switches = ctx.voluntary
            attr.no_ctxt_switches = ctx.involuntary
        else:
            elapsed_time = cur_time - attr.last_time
            attr.cswch = int((ctx.voluntary- attr.ctxt_switches ) / elapsed_time)
            attr.nvcswch = int((ctx.involuntary- attr.no_ctxt_switches) / elapsed_time)

            # print(f"({ctx.voluntary} - {attr.ctxt_switches}) / {elapsed_time}  = {attr.cswch}")
            # print(f"({ctx.involuntary} - {attr.no_ctxt_switches}) / {elapsed_time}  = {attr.nvcswch}")
            attr.ctxt_switches = ctx.voluntary
            attr.no_ctxt_switches = ctx.involuntary

    def statistic_io_rate(self, proc, attr, cur_time):
        # now_time = time.time()
        io_counters = proc.io_counters()
        if io_counters.read_bytes == 0 and io_counters.write_bytes == 0:
            attr.read_bytes = 0
            attr.write_bytes = 0
        else:
            elapsed_time = cur_time - attr.last_time
            attr.io_read = (io_counters.read_bytes - attr.read_bytes) / 1024 / elapsed_time
            attr.io_write = (io_counters.write_bytes - attr.write_bytes) / 1024 / elapsed_time
            attr.read_bytes = io_counters.read_bytes
            attr.write_bytes = io_counters.write_bytes

    def get_process_attr(self,proc_name):
        self.process_list = []
        cur_time = time.time()
        all_process_info = psutil.process_iter(ProcessIter)
        for proc in all_process_info:
            # print(proc.info)
            try:
                if proc.info["name"] == proc_name:
                    porc_name = proc.info["name"]
                    attr = Process_Attr(proc_name)
                    attr.time = cur_time
                    attr.time_stamp = time.strftime("%m%d-%X", time.localtime())
                    attr.pid = proc.info["pid"]
                    attr.cpu_percent = round(proc.info["cpu_percent"], 2)
                    attr.mem_percent = round(proc.info["memory_percent"], 2)
                    attr.mem_used = proc.info["memory_info"].rss / (1024 * 1024)
                    attr.running_stat = True
                    self.statistic_io_rate(proc, attr, cur_time)
                    self.statistic_ctx_switches(proc, attr, cur_time)
                    attr.status = proc.info["status"]
                    attr.uptime = int(cur_time - proc.info["create_time"])
                    attr.cpu_times = f'u:{proc.info["cpu_times"][0]} s:{proc.info["cpu_times"][1]}'
                    attr.open_files = len(proc.info["open_files"])
                    attr.num_threads = proc.info["num_threads"]
                    attr.last_time = cur_time

                    return attr
            except Exception as e:
                print("can't access process:",e)
                return None
