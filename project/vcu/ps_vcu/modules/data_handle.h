/*
 * @Author: dding3
 * @Date: 2025-03-14 09:52:14
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-24 14:46:13
 * @Description:
 * @FilePath: \ps_vcu\modules\data_handle.h
 */
#ifndef MODULES_DATA_HANDLE_H_
#define MODULES_DATA_HANDLE_H_

#include "modules/data_reader.h"

/**
 * @brief 初始化数据处理模块
 *
 */
void Data_Handle_Init(void);

/**
 * @brief 数据解析
 *
 */
void Data_Handle_Parse(DataReader *reader);

/**
 * @brief 写入can数据到缓存
 *
 * @param net 0:ACAN，1：CCAN
 * @param msg
 * @return int
 */
int Data_Handle_Write(CanNet net,CanMsg *msg);

/**
 * @brief 同步消息到can总线
 *
 */
void Data_Handle_Sync(void);

/**
 * @brief 设置id过滤
 *
 * @param ids
 * @param len
 * @return int
 */
int Data_Handle_SetFilter(uint32_t *ids, int len);

#endif // MODULES_DATA_HANDLE_H_
