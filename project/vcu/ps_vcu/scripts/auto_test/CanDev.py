r'''
Author: dding3
Date: 2025-04-16 17:26:43
LastEditors: dding3
LastEditTime: 2025-04-16 17:34:04
Description:
FilePath: \ps_vcu\scripts\auto_test\CanDev.py
'''

from enum import Enum
from ctypes import *
from CanMsg import CanMsg
import time
# 依赖的DLL文件(存放在根目录下)
CAN_DLL_PATH = './ControlCAN.dll'

# 读取DLL文件
Can_DLL = windll.LoadLibrary(CAN_DLL_PATH)

#状态正常
STATUS_OK = 1
#状态异常
STATUS_Failed = 0
# 保留字段
RESERVED = 0

# 接收帧ID
RECEIVE_ID = 0x0
# 发送帧ID
TRANSMIT_ID = 0x1
# 时间标识
TIME_STAMP = 0
# 是否使用时间标识
TIME_FLAG = 1
# 发送帧类型
TRANSMIT_SEND_TYPE = 1
# 接收帧类型
RECEIVE_SEND_TYPE = 0
# 是否是远程帧
REMOTE_FLAG = 0
# 是否是扩展帧
EXTERN_FLAG = 0
# 数据长度DLC
DATA_LEN = 8
# 用来接收的帧结构体数组的长度, 适配器中为每个通道设置了2000帧左右的接收缓存区
RECEIVE_LEN = 2500
# 接收保留字段
WAIT_TIME = 0
# 要发送的参数
TRANSMIT_DATA = 5
# 要发送的帧结构体数组的长度(发送的帧数量), 最大为1000, 建议设为1, 每次发送单帧, 以提高发送效率
TRANSMIT_LEN = 1

#波特率
class Buardrates(Enum):
    _500K = {"time0":0x00,"time1":0x1C}
    _1000K = {"time0":0x00,"time1":0x14}

#通道
class Channel(Enum):
    _0 = 0
    _1 = 1

#设备编号
class DevIndex(Enum):
    _0 = 0
    _1 = 1

#设备类型 USBCAN-2A, USBCAN-2C, CANalyst-II
class DevType(Enum):
    USB_CAN_2 = 4

# 通道初始化参数结构
# AccCode:  过滤验收码
# AccMask:  过滤屏蔽码
# Reserved: 保留字段
# Filter:   滤波模式 0/1=接收所有类型 2=只接收标准帧 3=只接收扩展帧
# Timing0:  波特率 T0
# Timing1:  波特率 T1
# Mode:     工作模式 0=正常工作 1=仅监听模式 2=自发自收测试模式
class VCI_CAN_INIT_CONFIG(Structure):
    _fields_ = [
        ("AccCode", c_uint),
        ("AccMask", c_uint),
        ("Reserved", c_uint),
        ("Filter", c_ubyte),
        ("Timing0", c_ubyte),
        ("Timing1", c_ubyte),
        ("Mode", c_ubyte)
    ]

class AccCode(Enum):
    Default = 0x80000000

class AccMask(Enum):
    ALL = 0xFFFFFFFF

class FilterMode(Enum):
    ALL = 0
    Standard_Only = 2
    Extend_Only = 3

class WorkMode(Enum):
    Normal = 0
    Monitor = 1
    LoopBack = 2


# CAN帧结构体
# ID:         帧ID, 32位变量, 数据格式为靠右对齐
# TimeStamp:  设备接收到某一帧的时间标识, 时间标示从CAN卡上电开始计时, 计时单位为0.1ms
# TimeFlag:   是否使用时间标识, 为1时TimeStamp有效, TimeFlag和TimeStamp只在此帧为接收帧时才有意义
# SendType:   发送帧类型 0=正常发送(发送失败会自动重发, 重发时间为4秒, 4秒内没有发出则取消) 1=单次发送(只发送一次, 发送失败不会自动重发, 总线只产生一帧数据)[二次开发, 建议1, 提高发送的响应速度]
# RemoteFlag: 是否是远程帧 0=数据帧 1=远程帧(数据段空)
# ExternFlag: 是否是扩展帧 0=标准帧(11位ID) 1=扩展帧(29位ID)
# DataLen:    数据长度DLC(<=8), 即CAN帧Data有几个字节, 约束了后面Data[8]中的有效字节
# Data:       CAN帧的数据, 由于CAN规定了最大是8个字节, 所以这里预留了8个字节的空间, 受DataLen约束, 如DataLen定义为3, 即Data[0]、Data[1]、Data[2]是有效的
# Reserved:   保留字段
class VCI_CAN_OBJ(Structure):
    _fields_ = [
        ("ID", c_uint),
        ("TimeStamp", c_uint),
        ("TimeFlag", c_ubyte),
        ("SendType", c_ubyte),
        ("RemoteFlag", c_ubyte),
        ("ExternFlag", c_ubyte),
        ("DataLen", c_ubyte),
        ("Data", c_ubyte * 8),
        ("Reserved", c_ubyte * 3)
     ]

class CanDev():

    """CanDev设备管理"""
    def __init__(self, index,buardrate):
        '''初始化CanDev设备索引和通道'''
        self.buardrate=buardrate #通道
        self.dev_index=index #设备
        self.is_open=False
        self.dev_type = DevType.USB_CAN_2 #设备类型
        self.init_config = VCI_CAN_INIT_CONFIG(AccCode.Default.value, AccMask.ALL.value, RESERVED, FilterMode.ALL.value, self.buardrate.value["time0"], self.buardrate.value["time1"], WorkMode.Normal.value)
        print("CanDev:创建设备 " + str(index.name) + " 波特率 " + self.buardrate.name)

    def open(self):
        '''开启设备，成功返回1，失败返回0'''
        if self.is_open:
            print("CanDev:设备已开启")
            return STATUS_Failed

        if Can_DLL.VCI_OpenDevice(self.dev_type.value, self.dev_index.value, RESERVED) != STATUS_OK:
            print('CanDev:连接设备 ' + str(self.dev_index.name) +' 失败')
            return STATUS_Failed

        self.is_open = True
        print("CanDev:开启设备 " + str(self.dev_index.name) + " 成功")
        return STATUS_OK

    def start(self,channel):
        if not self.is_open:
            print("CanDev:设备未开启")
            return STATUS_Failed

        if Can_DLL.VCI_InitCAN(self.dev_type.value, self.dev_index.value, channel.value, byref(self.init_config)) != STATUS_OK:
            print('CanDev:初始化通道 ' + str(channel.name) + ' 失败')
            return STATUS_Failed

        if Can_DLL.VCI_StartCAN(self.dev_type.value, self.dev_index.value, channel.value) != STATUS_OK:
            print('CanDev:启动通道 ' + str(channel.name) + ' 失败')
            return STATUS_Failed

        print('CanDev:启动通道 ' + str(channel.name) + ' 成功')
        return STATUS_OK

    def receive(self,channel):
        '''读取并返回can数据'''
        msg = {}
        if not self.is_open:
            print("CanDev:设备未开启")
            return msg

        ubyte_array_8 = c_ubyte * 8
        DATA = ubyte_array_8(RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED, RESERVED)
        ubyte_array_3 = c_ubyte * 3
        RESERVED_3 = ubyte_array_3(RESERVED, RESERVED, RESERVED)
        # 参数结构参考122行
        can_obj = VCI_CAN_OBJ(RECEIVE_ID, TIME_STAMP, TIME_FLAG, RECEIVE_SEND_TYPE, REMOTE_FLAG, EXTERN_FLAG, DATA_LEN, DATA, RESERVED_3)
        # VCI_USB_CAN_2: 设备类型
        # DEV_INDEX:     设备索引
        # can_index:     CAN通道索引
        # can_obj:       请求参数体
        # RECEIVE_LEN:   用来接收帧结构体数组的长度
        # WAIT_TIME:     保留参数
        ret = Can_DLL.VCI_Receive(self.dev_type.value, self.dev_index.value, channel.value, byref(can_obj), RECEIVE_LEN, WAIT_TIME)
        if ret == STATUS_OK:
            msg = CanMsg('unknown',can_obj.ID,can_obj.DataLen,list(can_obj.Data))
        return msg

    def receive_by_id(self,channel,id,timeout):
        time_start = time.time()

        while time.time()-time_start < timeout:
            msg = self.receive(channel)
            if msg != {} and msg.id == id:
                return msg

        return {}

    def transmit(self,channel,msg):
        '''发送can数据'''
        if not self.is_open:
            print("CanDev:设备未开启")
            return STATUS_Failed

        ubyte_array = c_ubyte*msg.dlc
        data = ubyte_array()

        for i in range(msg.dlc):
            data[i] = msg.data[i]

        ubyte_array_3 = c_ubyte * 3
        RESERVED_3 = ubyte_array_3(RESERVED, RESERVED, RESERVED)
        can_obj = VCI_CAN_OBJ(msg.id, TIME_STAMP, TIME_FLAG, TRANSMIT_SEND_TYPE, msg.rtr, msg.ext, msg.dlc, data, RESERVED_3)
        # VCI_USB_CAN_2: 设备类型
        # DEV_INDEX:     设备索引
        # can_index:     CAN通道索引
        # can_obj:       请求参数体
        # TRANSMIT_LEN:  发送的帧数量
        ret = Can_DLL.VCI_Transmit(self.dev_type.value, self.dev_index.value, channel.value, byref(can_obj), TRANSMIT_LEN)
        if ret == STATUS_OK:
            print('CanDev:发送通道 ' + str(channel.name) + ' 数据成功')
        else:
            print('CanDev:发送通道 ' + str(channel.name) + ' 数据失败')
        return ret
