#coding=utf-8
'''
Author: dding3
Date: 2024-02-19 00:08:00
LastEditors: dding3
LastEditTime: 2024-02-19 00:20:34
Description:
FilePath: /test/test/script/python/npc/NPC.py
'''
class NPC:
    def __init__(self):
        self.name = "飞雪"#input("给角色起个名字吧: ")
        self.gender = "男" #input("性别是？")
        self.personality = "豪爽" #input("描述角色的性格: ")
        self.age ="18"# input("角色的年龄: ")
        self.birthplace = "长白上"#input("角色的出生地: ")
        self.faction = "天龙"#input("角色所属的门派: ")
        self.background = "上古"#input("角色的历史背景: ")
        self.catchphrase = "天下第一"#input("角色的口头禅: ")
        self.self_assessment = "为我独尊"#input("角色的自我评价: ")

    def display_info(self):
        print("角色名: {self.name}")
        print("性别: {self.gender}")
        print("性格: {self.personality}")
        print("年龄: {self.age}")
        print("出生地: {self.birthplace}")
        print("门派: {self.faction}")
        print("历史背景: {self.background}")
        print("口头禅: {self.catchphrase}")
        print("自我评价: {self.self_assessment}")

from langchain import PromptTemplate
from langchain_community.llms import QianfanLLMEndpoint

llm = QianfanLLMEndpoint(model="Qianfan-Chinese-Llama-2-7B")

npc = NPC()
npc.display_info()
