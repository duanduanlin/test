import time
from dataclasses import dataclass, field
import psutil

@dataclass
class Cpu_Times:
    user: float = 0
    nice: float = 0
    system: float = 0
    idle: float = 0
    iowait: float = 0
    irq: float = 0
    softirq: float = 0
    guest: float = 0

@dataclass
class CpuAttr:
    time: float = 0
    time_stamp: str = ""
    cpu_percent: float = 0
    cpu_freq: list = field(default_factory=list)
    cpu_times: Cpu_Times = Cpu_Times()

class CpuAnalysis:
    def get_cpu_attr(self):
        attr = CpuAttr()
        attr.time = time.time()
        attr.time_stamp = time.strftime("%m-%d-%X", time.localtime())
        attr.cpu_freq = psutil.cpu_percent(interval=1, percpu=True)
        attr.cpu_percent = sum(attr.cpu_freq) / len(attr.cpu_freq)
        attr.cpu_times = psutil.cpu_times_percent()
        return attr
