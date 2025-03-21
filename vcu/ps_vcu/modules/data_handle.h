/*
 * @Author: dding3
 * @Date: 2025-03-14 09:52:14
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-14 10:14:04
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

#endif // MODULES_DATA_HANDLE_H_
