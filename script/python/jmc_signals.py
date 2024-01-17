
import os
import xlrd
import json
import re

file_suffix = '.xlsx'
file_prefix = 'jmc_signals_'

signal_file_base_path = './'
total_sheet_sign = 'TOTAL'
out_put_path = './output'

basic_sheet_index = 1
fault_sheet_index = 2

total_sheet_id_col_index = 1
total_sheet_name_col_index = 2

proj_sheet_id_col_index = 1
proj_sheet_size_col_index = 5
proj_sheet_accu_col_index = 7
proj_sheet_offset_col_index = 8

class Signalerror(RuntimeError):
    def __init__(self, arg):
        print(arg)
        self.args = arg

def _is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        pass

    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        pass

    return False

def _findAllFile(base,suffix,prefix):
    for root, ds, fs in os.walk(base):
        for f in fs:
            if f.endswith(suffix) and f.startswith(prefix) :
                fullname = os.path.join(root, f)
                yield fullname


def _getProjName(filePath):
    return filePath.replace(file_suffix,'').replace(file_prefix,'').replace('./','').lower()

def _check_path(proj):
    file_path = out_put_path+"/%s/" %(proj.lower())
    if not os.path.exists(file_path):
        os.makedirs(file_path)
    return file_path


def _dump_signal_json_file(file_path,signal_list):
    fo = open(file_path+"mcu_signals.json", "w+")
    fo.write(json.dumps(signal_list, sort_keys=True, indent=2, separators=(',', ': ')))
    fo.close()


def dump_signal_head_file(signal_list):
    head_file_contents = ""
    signal_enum = ""
    signal_id_list_handled = []
    head_file_contents+="#ifndef _MCU_SIGNALS_DEF_HPP_\r\n"
    head_file_contents+="#define _MCU_SIGNALS_DEF_HPP_\r\n\r\n"

    signal_enum+= "enum McuSignal {\r\n"
    for signal in signal_list:
         if signal["id"] not in signal_id_list_handled:
            signal_id_list_handled.append(signal["id"])
            signal_enum+="   %s = %d,\t\t //0X%04X\r\n" %(signal["name"],signal["id"],signal["id"])
    signal_enum+= "};//mcu signals\r\n\r\n"

    head_file_contents+= signal_enum
    head_file_contents+="#endif // _MCU_SIGNALS_DEF_HPP_"
    head_file_path = out_put_path + "/mcu_signals_def.hpp"

    # print(head_file_contents)
    fo = open(head_file_path, "w+")
    fo.write(head_file_contents)
    fo.close()


def get_signalList_total(filePath):
    id_list = []
    signal_list = []

    workbook = xlrd.open_workbook(filePath)
    table_basic = workbook.sheet_by_index(basic_sheet_index)
    table_fault = workbook.sheet_by_index(fault_sheet_index)

    id_col_list= table_basic.col_values(total_sheet_id_col_index)[1:]
    id_col_list.extend(table_fault.col_values(total_sheet_id_col_index)[1:])


    name_col_list= table_basic.col_values(total_sheet_name_col_index)[1:]
    name_col_list.extend(table_fault.col_values(total_sheet_name_col_index)[1:])

    print("got %d id total" % len(id_col_list))

    for i in range(0,len(id_col_list)):
        id = id_col_list[i]
        name = name_col_list[i]
        if id != '' and name != '//x':
            if id_col_list.count(id) != 1:
                raise Signalerror("conflict id:{}".format(id))
            if name_col_list.count(name) != 1:
                raise Signalerror("conflict name:{}".format(name))
            dt = {}
            dt["name"] = name
            dt["id"] = int(id,16)
            signal_list.append(dt)
            id_list.append(id)

    return id_list,signal_list

def scan_file(path):
    file_path = ''
    pro_list = []
    for i in _findAllFile(signal_file_base_path,file_suffix,file_prefix):
            if total_sheet_sign in i:
                file_path = i
            else:
                dt = {}
                dt["name"] = _getProjName(i)
                dt["path"] = i
                pro_list.append(dt)
    # print(pro_list)
    return file_path , pro_list


def get_signaList_proj(filePath):
    signal_list = []

    workbook = xlrd.open_workbook(filePath)
    table_basic = workbook.sheet_by_index(basic_sheet_index)
    table_fault = workbook.sheet_by_index(fault_sheet_index)

    id_col_list= table_basic.col_values(proj_sheet_id_col_index)[1:]
    id_col_list.extend(table_fault.col_values(proj_sheet_id_col_index)[1:])

    size_col_list= table_basic.col_values(proj_sheet_size_col_index)[1:]
    size_col_list.extend(table_fault.col_values(proj_sheet_size_col_index)[1:])

    accu_col_list= table_basic.col_values(proj_sheet_accu_col_index)[1:]
    offset_col_list= table_basic.col_values(proj_sheet_offset_col_index)[1:]

    # print(id_col_list)
    for i in range(0,len(id_col_list)):
        if id_col_list[i] != '' and _is_number(size_col_list[i]):
            dt = {}
            dt["name"] = id_col_list[i]
            dt["id"] = int(id_col_list[i],16)
            dt["size"] = int(size_col_list[i])
            if i < len(accu_col_list):
                dt["accu"] = float(accu_col_list[i])
                dt["offset"] = float(offset_col_list[i])
            else:
                dt["accu"] = 1.0
                dt["offset"] = 0.0
            signal_list.append(dt)
    return signal_list

def check_project_signal_list(signalList,idListTotal):
    id_list = []
    for signal in signalList:
        id = signal["name"]
        if id not in idListTotal:
            raise Signalerror("invalid id:{}".format(id))
        id_list.append(id)

    for id in id_list:
        if id_list.count(id) != 1:
            raise Signalerror("conflict id:{}".format(id))


total_sheet_file_path = ''
pro_list = []
signal_list_total = []
id_list_total = []
signal_list_map = {}

print(">>scan file...")
total_sheet_file_path, pro_list = scan_file(signal_file_base_path)
if total_sheet_file_path != '' and len(pro_list) > 0:
    print("got 1 total sheet and %d project sheet<<\r\n" % len(pro_list))
else:
    raise Signalerror('not find invalid total list or project list sheet')

print(">>check total sheet")
id_list_total,signal_list_total=get_signalList_total(total_sheet_file_path)
print("got %d valid signal <<\r\n" % len(signal_list_total))

print(">>check project sheet")
for pro in pro_list:
    signal_list = get_signaList_proj(pro["path"])
    print("proj:{0},signal num:{1}".format(pro["name"],len(signal_list)))
    check_project_signal_list(signal_list,id_list_total)
    signal_list_map[pro["name"]] = signal_list
# print(signal_list_map)
print("project sheet check done<<\r\n")

print(">>check output dir")
if os.path.exists(out_put_path):
    for root, dirs, files in os.walk(out_put_path, topdown=False):
        for name in files:
            os.remove(os.path.join(root, name))
        for name in dirs:
            os.rmdir(os.path.join(root, name))
print("check done<<\r\n")

print(">>dump signal head file")
dump_signal_head_file(signal_list_total)
print("signal head file dump done<<\r\n")

print(">>dump signal json file")
for (proj_name,signal_list) in signal_list_map.items():
    file_path = _check_path(proj_name)
    _dump_signal_json_file(file_path,signal_list)
print("json file dump done<<\r\n")

print(">>all done<<")
