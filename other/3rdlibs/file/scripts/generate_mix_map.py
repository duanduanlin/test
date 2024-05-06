'''
Author: dding3
Date: 2023-09-10 20:22:58
LastEditors: dding3
LastEditTime: 2023-09-10 23:32:06
Description:
FilePath: /jbox02/middleware/os/file/scripts/generate_mix_map.py
'''
import random

u8_list=range(0,256)
mix_list=range(0,256)
anti_list=range(0,256)

for i in range(0,256):
    val = random.choice(u8_list)
    mix_list[i]=val
    u8_list.remove(val)
    # print(i,val)

print(mix_list)
for i in range(0,256):
    # print(mix_list[i],i)
    anti_list[mix_list[i]]=i

print(anti_list)
