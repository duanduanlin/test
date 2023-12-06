'''
Author: dding3
Date: 2023-09-19 23:07:09
LastEditors: dding3
LastEditTime: 2023-09-19 23:50:42
Description:
FilePath: /test/commonapi/test/rpc/project/rpc_add/server.py
'''
from SimpleXMLRPCServer import SimpleXMLRPCServer
import ctypes

ll = ctypes.cdll.LoadLibrary
lib = ll("../../build/output/apps/lib/librpc_func.so")

def func_add(a,b):
    return lib.func_add(a,b)

if __name__ == '__main__':
    s = SimpleXMLRPCServer(('0.0.0.0',8080))
    s.register_function(func_add)
    print("server is online...")
    s.serve_forever()
