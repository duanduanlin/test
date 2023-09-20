'''
Author: dding3
Date: 2023-09-19 23:13:50
LastEditors: dding3
LastEditTime: 2023-09-19 23:19:34
Description:
FilePath: /test/commonapi/test/rpc/project/rpc_add/client.py
'''
from xmlrpclib import ServerProxy
s = ServerProxy("http://192.168.22.128:8080")
print(s.func_add(2,3))
