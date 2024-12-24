'''
Author: hanson
Date: 2024-12-24 15:44:29
LastEditors: hanson
LastEditTime: 2024-12-24 16:07:49
Description:
FilePath: \test\ros2\src\system_analysis\system_analysis\memory_analysis.py
'''
import time
from dataclasses import dataclass, field
import psutil

GB_BYTES = 1024 * 1024 * 1024

@dataclass
class MemoryAttr:
    time: float = 0
    time_stamp: str = ""
    mem_percent: float = 0
    mem_used: float = 0
    mem_buff: float = 0
    mem_cache: float = 0
    mem_free: float = 0
    mem_shared: float = 0
    mem_total: float = 0

class MemoryAnalysis:
    def get_mem_attr(self):
        # 内存使用情况
        mem_info = psutil.virtual_memory()
        attr = MemoryAttr()
        attr.time = time.time()
        attr.time_stamp = time.strftime("%m-%d-%X", time.localtime())
        attr.mem_percent = round(mem_info.percent, 2)  # 内存使用百分比
        # 内存单位GB
        attr.mem_used = round(mem_info.used / GB_BYTES, 2)
        attr.mem_buff = round(mem_info.buffers / GB_BYTES, 2)
        attr.mem_cache = round(mem_info.cached / GB_BYTES, 2)
        attr.mem_free = round(mem_info.free / GB_BYTES, 2)
        attr.mem_shared = round(mem_info.shared / GB_BYTES, 2)
        attr.mem_total = round(mem_info.total / GB_BYTES, 2)
        return attr
