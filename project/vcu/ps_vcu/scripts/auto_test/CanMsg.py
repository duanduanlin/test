'''
Author: dding3
Date: 2025-04-17 13:46:42
LastEditors: dding3
LastEditTime: 2025-04-28 11:02:12
Description:
FilePath: \ps_vcu\scripts\auto_test\CanMsg.py
'''

import cantools

class BasicSignals():
    '''创建一个结构化的can信号字典并将所有信息置0'''
    def __init__(self,name,signals):
        self.name = name
        self.signals = {}
        for signal in signals:
            self.signals[signal.name] = 0

class CanMsg():
    '''can桢封装'''
    def __init__(self,name,id,dlc,data=[],rtr=0,ext=0):
        self.name = name
        self.id = id
        self.dlc = dlc
        self.data = data
        self.rtr = rtr
        self.ext = ext

    def __str__(self):
        '''can桢格式化输出'''
        return f"{self.name}(id={self.id}, dlc={self.dlc}, data={self.data}, rtr={self.rtr}, ext={self.ext})"

class CanMsgParse():

    """CanMsg 解析"""
    def __init__(self, dbc):
        self.msg_map = {}
        self.db = cantools.database.load_file(dbc)
        # for message in self.db.messages:
        #     print(f'Message: {message.name} ({message.frame_id})')

    def encode(self,signals):
        '''can桢封装'''
        msg = self.db.get_message_by_name(signals.name)
        can_msg = CanMsg(signals.name,msg.frame_id,msg.length)
        if msg.is_extended_frame:
            can_msg.ext = 1
        # print('msg name {} signals {}'.format(signals.name,signals.signals))
        can_msg.data = list(self.db.encode_message(signals.name,signals.signals))
        return can_msg

    def decode(self,id,data):
        '''can桢解析'''
        return self.db.decode_message(id,bytes(data),decode_choices=False)


    def signal(self, name):
        '''根据信号名称创建结构化信号字典'''
        msg = self.db.get_message_by_name(name)
        return BasicSignals(name,msg.signals)

    def get_id_by_name(self, name):
        '''获取对应信号名称的id'''
        msg = self.db.get_message_by_name(name)
        return msg.frame_id
