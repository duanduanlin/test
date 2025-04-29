'''
Author: dding3
Date: 2025-04-16 16:01:50
LastEditors: dding3
LastEditTime: 2025-04-29 14:59:02
Description:
FilePath: \ps_vcu\scripts\auto_test\AutoTest.py
'''
r'''
Author: dding3
Date: 2025-04-16 16:01:50
LastEditors: dding3
LastEditTime: 2025-04-16 16:10:22
Description:
FilePath: \ps_vcu\scripts\auto_test\AutoTest.py
'''

import threading
import time
import signal

from CanDev import *
from CanMsg import *
from TestCase import *

class AutoTest():
    '''自动化测试'''
    def __init__(self):
        self.parse = CanMsgParse('./PSA-CAN.dbc')
        self.dev = CanDev(DevIndex._0,Buardrates._500K)
        self.dev.open()
        self.dev.start(Channel._0)
        self.dev.start(Channel._1)
        self.running = False
        self.cases = []
        self.cases.append(ADCU_SweepCmdTestCase(self.dev,self.parse))
        self.cases.append(ADCU_BrakeCmdTestCase(self.dev,self.parse))
        self.cases.append(ADCU_SteerCmdTestCase(self.dev,self.parse))
        self.cases.append(ADCU_DriveCmdTestCase(self.dev,self.parse))
        self.cases.append(ADCU_LampCmdTestCase(self.dev,self.parse))

        self.run_thread = threading.Thread(target=self.run)

        # self.send_thread = threading.Thread(target=self.can_send)
        # self.recv_thread = threading.Thread(target=self.can_recv)

    def run(self):
        for case in self.cases:
            case.run()

        for case in self.cases:
            case.report()

        global stop
        stop = True

    def can_send(self):
        while self.running:
            adcu_sweep_cmd = self.parse.signal("ADCU_SweepCmd")
            msg = self.parse.encode(adcu_sweep_cmd)
            print(msg)
            self.dev.transmit(Channel._1,msg)
            time.sleep(1)

    def can_recv(self):
        while self.running:
            msg = self.dev.receive(Channel._0)
            if msg != {}:
                print(msg)
                # print(self.parse.decode(msg.id,msg.data))

            time.sleep(1)

    def start(self):
        self.running = True
        self.run_thread.start()
        # self.send_thread.start()
        # self.recv_thread.start()

    def stop(self):
        self.running = False
        self.run_thread.join()
        # self.send_thread.join()
        # self.recv_thread.join()


# 自定义信号处理函数
def sigint_handler(signum, frame):
    global stop
    stop = True
    print("got ctrl + c")

stop = False

if __name__ == '__main__':
    auto_test = AutoTest()
    auto_test.start()

    # 设置相应信号处理的handler
    signal.signal(signal.SIGINT, sigint_handler)    #读取Ctrl+c信号

    while True:
        try:
            #读取到Ctrl+c前进行的操作
            if stop:
                # 中断时需要处理的代码
                print("will stop")
                auto_test.stop()
                break    #break只能退出当前循坏
                #中断程序需要用 raise
        except Exception as e:
            print(str(e))
            break
        time.sleep(0.1)
    print("done")
