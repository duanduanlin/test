#!/usr/bin/env python3
# coding:utf-8

""" 运行依赖
sudo apt install cpulimit

sudo su
pip3 install -i https://pypi.tuna.tsinghua.edu.cn/simple debugpy loguru
"""

import os
import shutil
import time
import psutil
from loguru import logger
from dataclasses import dataclass, field
from typing import List

# import debugpy
# debugpy.listen(6688)
# debugpy.wait_for_client()


@dataclass
class Monitor_Policy:
    disk_percent: float = 0
    timeout: int = 0
    action: str = "remove_and_compress"


@dataclass
class Monitor_Rules:
    monitor_disk: str
    monitor_dir: str
    policy: List[Monitor_Policy] = field(default_factory=dict)


@dataclass
class Match_Reserved_Dir:
    monitor_dir: str
    reserved: List[str] = field(default_factory=str)


Reserved_Dir_rules = [
    Match_Reserved_Dir(
        "/autocity",
        [
            "common-aarch64",
            "data",
            "docker",
            "logs",
            "lost+found",
            "opensource-aarch64",
            "ros_home",
            "run_package",
            "scripts",
            "sweeper",
            "vehicle",
            "rdcu",
            "workspace",
            "script",
            "config",
            "tmp",
        ],
    ),
    # Match_Reserved_Dir(
    #     "/home/autocity",
    #     [
    #         "calibration_param",
    #         "Documents",
    #         "Public",
    #         "Templates",
    #         "Downloads",
    #         "Music",
    #         "script",
    #         "Version",
    #         "bin",
    #         "Desktop",
    #         "Pictures",
    #         "Videos",
    #     ],
    # ),
]


Monitor_Service_Opt = {
    "log_path": "/autocity/data/record_log/remove_autocity_file.log",
    # "log_path": "clear_log_service",
    "rescan_time": 60 * 60,
    "reserved_dir_rules": Reserved_Dir_rules,
}

develop_phase_config = [
    Monitor_Rules(
        monitor_disk="/autocity",
        monitor_dir="/autocity/data/logs",
        policy=[
            # Monitor_Policy(50, 60 * 60 * 24 * 1, "compress"),
            Monitor_Policy(90, 1, "remove"),
            # Monitor_Policy(70, 60 * 60 * 12, "compress"),
            """Monitor_Policy(70, 60 * 60 * 24 * 1, "remove"),
            # Monitor_Policy(90, 60 * 60 * 6, "compress"),
            Monitor_Policy(93, 60 * 60 * 18, "remove"),
            Monitor_Policy(94, 60 * 60 * 16, "remove"),
            Monitor_Policy(95, 60 * 60 * 12, "remove"),
            Monitor_Policy(97, 60 * 60 * 6, "remove"),"""
        ],
    ),
    Monitor_Rules(
        monitor_disk="/autocity",
        monitor_dir="/autocity/data/record_log/remove_autocity_file.log",
        policy=[
            Monitor_Policy(90, 1, "remove"),
            #Monitor_Policy(95, 1, "remove"),
        ],
    ),
    Monitor_Rules(
        monitor_disk="/autocity",
        monitor_dir="/autocity/logs",
        policy=[
            #Monitor_Policy(80, 1, "remove"),
            Monitor_Policy(90, 1, "remove"),
        ],
    ),
    Monitor_Rules(
        monitor_disk="/autocity",
        monitor_dir="/autocity/tmp",
        policy=[
            #Monitor_Policy(80, 1, "remove"),
            Monitor_Policy(95, 1, "remove"),
        ],
    ),
    Monitor_Rules(
        monitor_disk="/",
        monitor_dir="/home/autocity/Downloads",
        policy=[
            Monitor_Policy(70, 60 * 60 * 24 * 5, "remove"),
            Monitor_Policy(80, 60 * 60 * 24 * 3, "remove"),
            Monitor_Policy(90, 60 * 60 * 24 * 1, "remove"),
        ],
    ),
    Monitor_Rules(
        monitor_disk="/",
        monitor_dir="/home/autocity/.local/share/Trash",
        policy=[
            Monitor_Policy(70, 60 * 60 * 24 * 5, "remove"),
            Monitor_Policy(80, 60 * 60 * 24 * 3, "remove"),
            Monitor_Policy(90, 60 * 60 * 24 * 1, "remove"),
        ],
    ),
    Monitor_Rules(
        monitor_disk="/",
        monitor_dir="/home/autocity/.cache",
        policy=[
            Monitor_Policy(80, 60 * 60 * 24 * 5, "remove"),
            # Monitor_Policy(80, 60 * 60 * 24 * 3, "remove"),
            # Monitor_Policy(90, 60 * 60 * 24 * 1, "remove"),
        ],
    ),
]


class Monitor_Service:
    def __init__(self, config, opt):
        self.config = config
        self.opt = opt
        self.rescan_time = opt["rescan_time"]
        self.log_path = opt["log_path"]
        self.init_log()

    def init_log(self):
        log_format = "[{time:YYYYMMDD-HH:mm:ss} {level}] {message}"
        logger.add("%s/{time}.log" % (self.log_path), format=log_format)

    def delete_old_files_and_dirs_count(self, path, delate_count):
        entries = []
        with os.scandir(path) as dirs:
            for entry in dirs:
                if not entry.is_symlink():  #排除软链接
                    entries.append((entry.path, entry.stat().st_mtime))

        entries.sort(key=lambda x: x[1], reverse=True)
        #for path, mtime in entries:
        #   print(f"Path: {path}, Last modified time: {mtime}")
        if not entries:  # 检查 entries 是否为空
            logger.debug(f"No target to delete.")
            exit
            
        for path, mtime in entries[-delate_count:]:
            try:
                if os.path.isdir(path):
                    #os.system(f"rm -rf {path}")
                    shutil.rmtree(path)
                else:
                    os.remove(path)  
                logger.debug(f"Deleted: {path}")
            except Exception as e:
                logger.debug(f"Failed to delete {path}: {e}")

        

    def delete_old_files_and_dirs_v2(self, path, timeout_time):
        current_time = time.time()

        for entry in os.scandir(path):
            try:
                entry_mtime = entry.stat().st_mtime
                # 计算时间差（以秒为单位）
                time_diff = current_time - entry_mtime

                if entry.is_file():
                    if time_diff > timeout_time:
                        logger.debug(f"del {entry.path}")
                        os.remove(entry.path)
                elif entry.is_dir():
                    # 如果是目录，递归调用函数处理子目录
                    self.delete_old_files_and_dirs(entry.path, timeout_time)
                    if not os.listdir(entry.path) and time_diff > timeout_time:
                        logger.debug(f"del dir: {entry.path}")
                        os.rmdir(entry.path)

            except Exception as e:
                logger.error(f"Error processing {entry}: {e}")
                try:
                    os.remove(entry.path)
                except:
                    continue

    def compress_ro_remove_log(self, entry, action):
        path = entry.path
        if action == "compress":
            # 检查压缩标志
            if os.path.exists(f"{path}/zstd") == True:
                return

            path_mtime = entry.stat().st_mtime
            module_dir = os.listdir(path)
            for module in module_dir:
                if module in ["record"]:
                    # os.system(f"tar -I zstd -cf {path}/{module}.tar.zst {path}/{module}")
                    pass
                elif ".zst" in "module":
                    continue
                else:
                    cmd = f"cpulimit -l 20 -c 1 -f -- zstd -r --rm {path}/{module}"
                    os.system(cmd)
                    # cmd = ['cpulimit', '-l', '20', '-c', '1', '--', 'zstd', '-r', '--rm', f"{path}/{module}"]
                    # ret = subprocess.run(cmd)

            # 创建已压缩标志
            os.system(f"touch {path}/zstd")
            os.utime(path, (path_mtime, path_mtime))
        elif action == "remove":
            logger.debug(f"del: {path}")
            os.system(f"rm -rf {path}")

    def list_top_dir(self, rule, policy):
        scan_path = rule.monitor_dir
        timeout_time = policy.timeout
        current_time = time.time()
        with os.scandir(scan_path) as dirs:
            for entry in dirs:
                entry_mtime = entry.stat().st_mtime
                diff_time = current_time - entry_mtime
                if diff_time > timeout_time:
                    self.compress_ro_remove_log(entry, policy.action)

    def remove_not_reserved_dir(self):
        rules = self.opt["reserved_dir_rules"]
        for rule in rules:
            monitor_dir = rule.monitor_dir
            reserved = rule.reserved
            with os.scandir(monitor_dir) as dirs:
                for entry in dirs:
                    if entry.name in reserved:
                        # logger.debug(f"reserved {entry.path}")
                        pass
                    else:
                        # 排除隐藏目录 '.xxx'
                        if entry.name[0] == '.':
                            continue
                        #logger.debug(f"remove: {entry.path}")
                        # shutil.rmtree(entry.path, ignore_errors=True)

    def monitor_and_clean_log(self):
        self.remove_not_reserved_dir()
        for rule in self.config:
            mount_point = rule.monitor_disk
            cur_pwd = os.getcwd()
            if os.path.exists(rule.monitor_dir) == False:
                continue

            os.chdir(rule.monitor_dir)
            for item_policy in rule.policy:
                disk_info = psutil.disk_usage(mount_point)
                if disk_info.percent >= item_policy.disk_percent:
                    logger.info(
                        f"disk uage: {mount_point}:{disk_info.percent} > {item_policy.disk_percent}"
                    )
                    if rule.monitor_disk == "/":
                        self.list_top_dir(rule, item_policy)
                    else:
                        start_time = time.time()
                        while disk_info.percent >= item_policy.disk_percent:
                            self.delete_old_files_and_dirs_count(rule.monitor_dir, item_policy.timeout)
                            disk_info = psutil.disk_usage(mount_point)
                            current_time = time.time()  #超时处理
                            if(current_time - start_time > 5):
                                logger.debug(f"time out 5s!!! start_time:{start_time} current_time:{current_time}  disk_percent: {disk_info.percent}")
                                break
                        #logger.debug(f"time: start_time:{start_time} current_time:{current_time}")
                else:
                    break
            os.chdir(cur_pwd)

    def loop_run(self):
        while True:
            self.monitor_and_clean_log()
            time.sleep(self.rescan_time)


def main():
    monitor = Monitor_Service(develop_phase_config, Monitor_Service_Opt)
    # monitor.loop_run()
    monitor.monitor_and_clean_log()


if __name__ == "__main__":
    main()
