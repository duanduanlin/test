'''
Author: dding3
Date: 2025-04-18 09:52:21
LastEditors: dding3
LastEditTime: 2025-04-30 10:47:02
Description:
FilePath: \ps_vcu\scripts\auto_test\TestCase.py
'''
from enum import Enum
from time import sleep

from CanDev import *
from CanMsg import *
class TestResult(Enum):
    default = 0
    succeed = 1
    failed = 2

class TryValues():
    def __init__(self,sig,value):
        self.sig = sig
        self.value = value

class TrySignals():
    def __init__(self,req_name,res_name,req_channel=Channel._1,res_channel=Channel._0):
        self.req_name = req_name
        self.res_name = res_name
        self.req_values=[]
        self.res_values=[]
        self.req_channel = req_channel
        self.res_channel = res_channel

    def add_req(self,req):
        self.req_values.append(req)

    def add_res(self,res):
        self.res_values.append(res)

class Case():
    def __init__(self,name,func):
        self.name = name
        self.func = func
        self.result = TestResult.default

    def run(self):
        print("Run case {}".format(self.name))
        self.result = self.func()
        return self.result

    def report(self):
        print("case {} test {}".format(self.name,self.result.name))

class BasicTestCase():
    '''基本测试用例'''
    def __init__(self,name):
        self.name = name
        self.cases = []
        self.total_num = 0
        self.failed_num = 0
        self.succ_num = 0

    def run(self):
        '''运行测试用例'''
        print("Run {} TestCase".format(self.name))
        for case in self.cases:
            if case.run() == TestResult.succeed:
                self.succ_num+=1
            else:
                self.failed_num+=1

    def report(self):
        for case in self.cases:
            case.report()
        print("Case {},total num {},failed num {},succeed num {}".format(self.name,self.total_num,self.failed_num,self.succ_num))

    def add(self,case):
        self.cases.append(case)
        self.total_num+=1

    def try_signal(self,signal):
        try_count = 0

        req_cmd = self.parse.signal(signal.req_name)
        for value in signal.req_values:
            print("try sig {} value {}".format(value.sig,value.value))
            req_cmd.signals[value.sig]=value.value

        msg = self.parse.encode(req_cmd)

        while try_count < 3:
            self.dev.transmit(signal.req_channel,msg)
            sleep(0.1)
            res_id = self.parse.get_id_by_name(signal.res_name)
            res_msg = self.dev.receive_by_id(signal.res_channel,res_id,1)
            if res_msg != {}:
                res_ok_count = 0
                res_signals = self.parse.decode(res_msg.id,res_msg.data)
                for value in signal.res_values:
                    print("check sig {} except value {} Actual value {}".format(value.sig,value.value,res_signals[value.sig]))
                    if res_signals[value.sig] == value.value:
                        res_ok_count+=1
                if res_ok_count == len(signal.res_values):
                    print("try succeed")
                    return TestResult.succeed
            else:
                print('no such msg recv {}({})'.format(signal.res_name,res_id))
            sleep(1)
            try_count+=1
        return TestResult.failed


class ADCU_SweepCmdTestCase(BasicTestCase):
    def __init__(self,dev,parse):
        BasicTestCase.__init__(self,"ADCU_SweepCmdCase")
        self.dev = dev
        self.parse = parse
        ADCU_FenderCtrlCase = Case('ADCU_FenderCtrlCase',self.ADCU_FenderCtrlTest)
        ADCU_OneClkCleanCtrlCase = Case('ADCU_OneClkCleanCtrlCase',self.ADCU_OneClkCleanCtrlTest)
        ADCU_OneClkDumpCtrlCase = Case('ADCU_OneClkDumpCtrlCase',self.ADCU_OneClkDumpCtrlTest)

        self.add(ADCU_OneClkDumpCtrlCase)
        self.add(ADCU_OneClkCleanCtrlCase)
        self.add(ADCU_FenderCtrlCase)

    def ADCU_OneClkDumpCtrlTest(self):
        succ_count = 0

        #1.测试开启
        print("try open ADCU_OneClkDumpCtrlTest")
        try_signals_open = TrySignals('ADCU_SweepCmd','VCU_SweepStatus')
        try_signals_open.add_req(TryValues('ADCU_OneClkDumpCtrl',1))
        try_signals_open.add_res(TryValues('VCU_OneClkDump_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try close ADCU_OneClkDumpCtrlTest")
        try_signals_close = TrySignals('ADCU_SweepCmd','VCU_SweepStatus')
        try_signals_close.add_req(TryValues('ADCU_OneClkDumpCtrl',2))
        try_signals_close.add_res(TryValues('VCU_OneClkDump_Sts',2))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_OneClkCleanCtrlTest(self):
        succ_count = 0

        #1.测试开启
        print("try open ADCU_OneClkCleanCtrlTest")
        try_signals_open = TrySignals('ADCU_SweepCmd','VCU_SweepStatus')
        try_signals_open.add_req(TryValues('ADCU_OneClkCleanCtrl',1))
        try_signals_open.add_res(TryValues('VCU_OneClkClean_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try close ADCU_OneClkCleanCtrlTest")
        try_signals_close = TrySignals('ADCU_SweepCmd','VCU_SweepStatus')
        try_signals_close.add_req(TryValues('ADCU_OneClkCleanCtrl',2))
        try_signals_close.add_res(TryValues('VCU_OneClkClean_Sts',2))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_FenderCtrlTest(self):
        succ_count = 0

        #1.测试开启
        print("try open ADCU_FenderCtrl")
        try_signals_open = TrySignals('ADCU_SweepCmd','VCU_SweepStatus')
        try_signals_open.add_req(TryValues('ADCU_FenderCtrl',1))
        try_signals_open.add_res(TryValues('VCU_Fender_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try close ADCU_FenderCtrl")
        try_signals_close = TrySignals('ADCU_SweepCmd','VCU_SweepStatus')
        try_signals_close.add_req(TryValues('ADCU_FenderCtrl',2))
        try_signals_close.add_res(TryValues('VCU_Fender_Sts',2))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed


class ADCU_BrakeCmdTestCase(BasicTestCase):
    def __init__(self,dev,parse):
        BasicTestCase.__init__(self,"ADCU_BrakeCmdCase")
        self.dev = dev
        self.parse = parse
        ADCU_Brk_ParkEnableCase = Case('ADCU_Brk_ParkEnableCase',self.ADCU_Brk_ParkEnableCtrlTest)
        ADCU_Brk_CtrlModeCase = Case('ADCU_Brk_CtrlModeCase',self.ADCU_Brk_CtrlModeTest)
        ADCU_Brk_TgtPedposCase = Case('ADCU_Brk_TgtPedposCase',self.ADCU_Brk_TgtPedposTest)

        self.add(ADCU_Brk_ParkEnableCase)
        self.add(ADCU_Brk_CtrlModeCase)
        self.add(ADCU_Brk_TgtPedposCase)

    def ADCU_Brk_TgtPedposTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Brk_TgtPedposTest")
        try_signals_open = TrySignals('ADCU_BrakeCmd','VCU_BrakeStatus')
        try_signals_open.add_req(TryValues('ADCU_Brk_TgtPedpos',50))
        try_signals_open.add_res(TryValues('VCU_Brk_ActPedpos',50))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Brk_TgtPedposTest")
        try_signals_close = TrySignals('ADCU_BrakeCmd','VCU_BrakeStatus')
        try_signals_close.add_req(TryValues('ADCU_Brk_TgtPedpos',100))
        try_signals_close.add_res(TryValues('VCU_Brk_ActPedpos',100))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_Brk_CtrlModeTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Brk_CtrlModeTest")
        try_signals_open = TrySignals('ADCU_BrakeCmd','VCU_BrakeStatus')
        try_signals_open.add_req(TryValues('ADCU_Brk_TgtPedpos',1))
        try_signals_open.add_res(TryValues('VCU_Brk_CtrlModeSts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Brk_ParkEnableCtrl")
        try_signals_close = TrySignals('ADCU_BrakeCmd','VCU_BrakeStatus')
        try_signals_close.add_req(TryValues('ADCU_Brk_CtrlMode',0))
        try_signals_close.add_res(TryValues('VCU_Brk_CtrlModeSts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_Brk_ParkEnableCtrlTest(self):
        succ_count = 0

        #1.测试开启
        print("try open ADCU_Brk_ParkEnableCtrl")
        try_signals_open = TrySignals('ADCU_BrakeCmd','VCU_BrakeStatus')
        try_signals_open.add_req(TryValues('ADCU_Brk_ParkEnable',1))
        try_signals_open.add_res(TryValues('VCU_Brk_ParkEnableSts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try close ADCU_Brk_ParkEnableCtrl")
        try_signals_close = TrySignals('ADCU_BrakeCmd','VCU_BrakeStatus')
        try_signals_close.add_req(TryValues('ADCU_Brk_ParkEnable',0))
        try_signals_close.add_res(TryValues('VCU_Brk_ParkEnableSts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed


class ADCU_SteerCmdTestCase(BasicTestCase):
    def __init__(self,dev,parse):
        BasicTestCase.__init__(self,"ADCU_SteerCmdCase")
        self.dev = dev
        self.parse = parse
        ADCU_Str_WorkModeCase = Case('ADCU_Str_WorkModeCase',self.ADCU_Str_WorkModeTest)
        ADCU_Str_TgtAngleCase = Case('ADCU_Str_WorkModeCase',self.ADCU_Str_TgtAngleTest)

        self.add(ADCU_Str_WorkModeCase)
        self.add(ADCU_Str_TgtAngleCase)

    def ADCU_Str_WorkModeTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Str_WorkModeTest")
        try_signals_open = TrySignals('ADCU_SteerCmd','VCU_SteerStatus')
        try_signals_open.add_req(TryValues('ADCU_Str_WorkMode',1))
        try_signals_open.add_res(TryValues('VCU_Str_WorkMode',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Str_WorkModeTest")
        try_signals_close = TrySignals('ADCU_SteerCmd','VCU_SteerStatus')
        try_signals_close.add_req(TryValues('ADCU_Str_WorkMode',0))
        try_signals_close.add_res(TryValues('VCU_Str_WorkMode',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_Str_TgtAngleTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Str_TgtAngleTest")
        try_signals_open = TrySignals('ADCU_SteerCmd','VCU_SteerStatus')
        try_signals_open.add_req(TryValues('ADCU_Str_TgtAngle',3.14/2))
        try_signals_open.add_res(TryValues('VCU_Str_Angle',3.14/2))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Str_TgtAngleTest")
        try_signals_close = TrySignals('ADCU_SteerCmd','VCU_SteerStatus')
        try_signals_close.add_req(TryValues('ADCU_Str_TgtAngle',0))
        try_signals_close.add_res(TryValues('VCU_Str_Angle',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

class ADCU_DriveCmdTestCase(BasicTestCase):
    def __init__(self,dev,parse):
        BasicTestCase.__init__(self,"ADCU_DriveCmdCase")
        self.dev = dev
        self.parse = parse
        ADCU_Drv_TgtGearCase = Case('ADCU_Drv_TgtGearCase',self.ADCU_Drv_TgtGearTest)
        ADCU_Drv_CtrlModeCase = Case('ADCU_Drv_CtrlModeCase',self.ADCU_Drv_CtrlModeTest)
        ADCU_DrvingModeCase = Case('ADCU_DrvingModeCase',self.ADCU_DrvingModeTest)
        ADCU_Drv_TgtPedposCase = Case('ADCU_Drv_TgtPedposCase',self.ADCU_Drv_TgtPedposTest)
        ADCU_Drv_TgtVehSpdCase = Case('ADCU_Drv_TgtVehSpdCase',self.ADCU_Drv_TgtVehSpdTest)
        ADCU_Drv_VehSpdLimitCase = Case('ADCU_Drv_VehSpdLimitCase',self.ADCU_Drv_VehSpdLimitTest)

        self.add(ADCU_Drv_TgtGearCase)
        self.add(ADCU_Drv_CtrlModeCase)
        self.add(ADCU_DrvingModeCase)
        self.add(ADCU_Drv_TgtPedposCase)
        self.add(ADCU_Drv_TgtVehSpdCase)
        self.add(ADCU_Drv_VehSpdLimitCase)

    def ADCU_Drv_TgtGearTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Drv_TgtGearTest")
        try_signals_open = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_open.add_req(TryValues('ADCU_Drv_TgtGear',1))
        try_signals_open.add_res(TryValues('VCU_Drv_Gear',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Drv_TgtGearTest")
        try_signals_close = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_close.add_req(TryValues('ADCU_Drv_TgtGear',0))
        try_signals_close.add_res(TryValues('VCU_Drv_Gear',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_Drv_CtrlModeTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Drv_CtrlModeTest")
        try_signals_open = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_open.add_req(TryValues('ADCU_Drv_CtrlMode',1))
        try_signals_open.add_res(TryValues('VCU_Drv_CtrlMode',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Drv_CtrlModeTest")
        try_signals_close = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_close.add_req(TryValues('ADCU_Drv_CtrlMode',0))
        try_signals_close.add_res(TryValues('VCU_Drv_CtrlMode',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_DrvingModeTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_DrvingModeTest")
        try_signals_1 = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_1.add_req(TryValues('ADCU_DrvingMode',1))
        try_signals_1.add_res(TryValues('VCU_DrvingMode',1))

        if self.try_signal(try_signals_1) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_DrvingModeTest")
        try_signals_0 = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_0.add_req(TryValues('ADCU_DrvingMode',0))
        try_signals_0.add_res(TryValues('VCU_DrvingMode',0))

        if self.try_signal(try_signals_0) == TestResult.succeed:
            succ_count+=1

        print("try change ADCU_DrvingModeTest")
        try_signals_2 = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_2.add_req(TryValues('ADCU_DrvingMode',2))
        try_signals_2.add_res(TryValues('VCU_DrvingMode',2))

        if self.try_signal(try_signals_2) == TestResult.succeed:
            succ_count+=1

        print("try change ADCU_DrvingModeTest")
        try_signals_4 = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_4.add_req(TryValues('ADCU_DrvingMode',4))
        try_signals_4.add_res(TryValues('VCU_DrvingMode',4))

        if self.try_signal(try_signals_4) == TestResult.succeed:
            succ_count+=1

        if succ_count == 4:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_Drv_TgtPedposTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Drv_TgtPedposTest")
        try_signals_open = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_open.add_req(TryValues('ADCU_Drv_TgtPedpos',50))
        try_signals_open.add_res(TryValues('VCU_Drv_ActPedpos',50))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Drv_TgtPedposTest")
        try_signals_close = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_close.add_req(TryValues('ADCU_Drv_TgtPedpos',0))
        try_signals_close.add_res(TryValues('VCU_Drv_ActPedpos',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_Drv_TgtVehSpdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Drv_TgtVehSpdTest")
        try_signals_open = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_open.add_req(TryValues('ADCU_Drv_TgtVehSpd',5))
        try_signals_open.add_res(TryValues('VCU_Drv_ActVehSpd',5))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Drv_TgtVehSpdTest")
        try_signals_close = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_close.add_req(TryValues('ADCU_Drv_TgtVehSpd',0))
        try_signals_close.add_res(TryValues('VCU_Drv_ActVehSpd',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_Drv_VehSpdLimitTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Drv_VehSpdLimitTest")
        try_signals_open = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_open.add_req(TryValues('ADCU_Drv_VehSpdLimit',5))
        try_signals_open.add_res(TryValues('VCU_Drv_ActVehSpd',5))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Drv_VehSpdLimitTest")
        try_signals_close = TrySignals('ADCU_DriveCmd','VCU_DriveStatus')
        try_signals_close.add_req(TryValues('ADCU_Drv_VehSpdLimit',0))
        try_signals_close.add_res(TryValues('VCU_Drv_ActVehSpd',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed


class ADCU_LampCmdTestCase(BasicTestCase):
    def __init__(self,dev,parse):
        BasicTestCase.__init__(self,"ADCU_LampCmdCase")
        self.dev = dev
        self.parse = parse
        ADCU_WarningLamp_CmdCase = Case('ADCU_WarningLamp_CmdCase',self.ADCU_WarningLamp_CmdTest)
        ADCU_Horn_CmdCase = Case('ADCU_Horn_CmdCase',self.ADCU_Horn_CmdTest)
        ADCU_Buzzer_CmdCase = Case('ADCU_Buzzer_CmdCase',self.ADCU_Buzzer_CmdTest)
        ADCU_BackLamp_CmdCase = Case('ADCU_BackLamp_CmdCase',self.ADCU_BackLamp_CmdTest)
        ADCU_TurnRLamp_CmdCase = Case('ADCU_TurnRLamp_CmdCase',self.ADCU_TurnRLamp_CmdTest)
        ADCU_TurnLLamp_CmdCase = Case('ADCU_TurnLLamp_CmdCase',self.ADCU_TurnLLamp_CmdTest)
        ADCU_DblFlashLamp_CmdCase = Case('ADCU_DblFlashLamp_CmdCase',self.ADCU_DblFlashLamp_CmdTest)
        ADCU_HeadLamp_CmdCase = Case('ADCU_HeadLamp_CmdCase',self.ADCU_HeadLamp_CmdTest)
        ADCU_RearHeadLamp_CmdCase = Case('ADCU_RearHeadLamp_CmdCase',self.ADCU_RearHeadLamp_CmdTest)
        ADCU_WidthLamp_CmdCase = Case('ADCU_WidthLamp_CmdCase',self.ADCU_WidthLamp_CmdTest)
        ADCU_FillLamp_CmdCase = Case('ADCU_FillLamp_CmdCase',self.ADCU_FillLamp_CmdTest)
        ADCU_BrkLamp_CmdCase = Case('ADCU_BrkLamp_CmdCase',self.ADCU_BrkLamp_CmdTest)

        self.add(ADCU_BrkLamp_CmdCase)
        self.add(ADCU_FillLamp_CmdCase)
        self.add(ADCU_WidthLamp_CmdCase)
        self.add(ADCU_RearHeadLamp_CmdCase)
        self.add(ADCU_HeadLamp_CmdCase)
        self.add(ADCU_DblFlashLamp_CmdCase)
        self.add(ADCU_TurnLLamp_CmdCase)
        self.add(ADCU_TurnRLamp_CmdCase)
        self.add(ADCU_BackLamp_CmdCase)
        self.add(ADCU_Buzzer_CmdCase)
        self.add(ADCU_WarningLamp_CmdCase)
        self.add(ADCU_Horn_CmdCase)

    def ADCU_BrkLamp_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_BrkLamp_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_BrkLamp_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_BrakeLamp_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_BrkLamp_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_BrkLamp_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_BrakeLamp_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_FillLamp_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_FillLamp_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_FillLamp_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_FillLamp_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_FillLamp_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_FillLamp_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_FillLamp_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_WidthLamp_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_WidthLamp_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_WidthLamp_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_WidthLamp_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_WidthLamp_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_WidthLamp_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_WidthLamp_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_RearHeadLamp_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_RearHeadLamp_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_RearHeadLamp_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_RearHeadLamp_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_RearHeadLamp_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_RearHeadLamp_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_RearHeadLamp_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_HeadLamp_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_HeadLamp_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_HeadLamp_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_HeadLamp_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_HeadLamp_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_HeadLamp_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_HeadLamp_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_DblFlashLamp_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_DblFlashLamp_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_DblFlashLamp_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_DblFlashLamp_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_DblFlashLamp_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_DblFlashLamp_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_DblFlashLamp_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_TurnLLamp_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_TurnLLamp_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_TurnLLamp_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_TurnLLamp_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_TurnLLamp_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_TurnLLamp_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_TurnLLamp_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_TurnRLamp_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_TurnRLamp_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_TurnRLamp_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_TurnRLamp_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_TurnRLamp_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_TurnRLamp_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_TurnRLamp_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_BackLamp_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_BackLamp_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_BackLamp_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_ReverseLamp_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_BackLamp_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_BackLamp_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_ReverseLamp_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_Buzzer_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Buzzer_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_Buzzer_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_Buzzer_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Buzzer_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_Buzzer_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_Buzzer_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_Horn_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_Horn_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_Horn_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_Horn_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_Horn_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_Horn_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_Horn_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed

    def ADCU_WarningLamp_CmdTest(self):
        succ_count = 0

        #1.测试开启
        print("try change ADCU_WarningLamp_CmdTest")
        try_signals_open = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_open.add_req(TryValues('ADCU_WarningLamp_Cmd',1))
        try_signals_open.add_res(TryValues('VCU_WarningLamp_Sts',1))

        if self.try_signal(try_signals_open) == TestResult.succeed:
            succ_count+=1

        #2.测试关闭
        print("try change ADCU_WarningLamp_CmdTest")
        try_signals_close = TrySignals('ADCU_LampCmd','VCU_LampStatus')
        try_signals_close.add_req(TryValues('ADCU_WarningLamp_Cmd',0))
        try_signals_close.add_res(TryValues('VCU_WarningLamp_Sts',0))

        if self.try_signal(try_signals_close) == TestResult.succeed:
            succ_count+=1

        if succ_count == 2:
            return TestResult.succeed

        return TestResult.failed
