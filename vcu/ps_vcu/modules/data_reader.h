/*
 * @Author: hanson
 * @Date: 2025-02-17 10:45:44
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-14 11:32:32
 * @Description:
 * @FilePath: \ps_vcu\modules\data_reader.h
 */
#ifndef MODULES_DATA_READER_H_
#define MODULES_DATA_READER_H_

#include "fdcan.h"
#include "common/vcu_status.h"

typedef struct data_reader
{
    // todo
    // chassis_cmd
    ChassisCmd chassis_cmd;
    // chassis
    ChassisStatus chassis_status;
} DataReader; // 数据接收结构

/**
 * @brief can数据处理
 *
 * @param msg
 * @param reader
 * @return void
 */
void Can_Msg_Parse(CanMsg *msg, DataReader *reader);

/**
 * @brief 获取指定can网络的ID数组
 *
 * @param net
 * @param ids
 * @param size
 * @return int
 */
int Can_Msg_GetIds(CanNet net,uint32_t *ids, int size);

#endif // MODULES_DATA_READER_H_
