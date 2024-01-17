'''
Author: dding3
Date: 2024-01-16 22:36:46
LastEditors: dding3
LastEditTime: 2024-01-16 23:29:06
Description:
FilePath: /test/test/script/python/jmc_serial.py
'''
import serial
import threading

import serial.tools.list_ports

STRGLO=""
BOOL=True

def listPort():
    port_list = list(serial.tools.list_ports.comports())
    print(port_list)
    if len(port_list) == 0:
        print('no serial find')
    else:
        for i in range(0,len(port_list)):
            print(port_list[i])

def ReadData(ser):
    global STRGLO,BOOL
    while BOOL:
        if ser.in_waiting:
            STRGLO = ser.read(ser.in_waiting).decode("gbk")
            print(STRGLO)
            if(STRGLO=="exit"):
                break

def DOpenPort(portx,bps,timeout):
    ret=False
    try:
        ser = serial.Serial(portx, bps, timeout=timeout)
        if(ser.is_open):
            ret=True
            threading.Thread(target=ReadData, args=(ser,)).start()
    except Exception as e:
        print("---error---:", e)
    return ser,ret

def DColsePort(ser):
    global BOOL
    BOOL=False
    ser.close()

def DWritePort(ser,text):
    result = ser.write(text.encode("gbk"))
    return result

def DReadPort():
    global STRGLO
    str=STRGLO
    STRGLO=""
    return str

if __name__=="__main__":
    listPort()
    ser,ret=DOpenPort("/dev/ttyUSB0",115200,None)
    if(ret==True):
        count=DWritePort(ser,"hello world")
        print("write count:",count)
