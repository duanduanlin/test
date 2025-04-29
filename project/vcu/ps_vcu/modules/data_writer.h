/*
 * @Author: hanson
 * @Date: 2025-02-21 15:33:07
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-24 11:43:06
 * @Description:
 * @FilePath: \ps_vcu\modules\data_writer.h
 */
#ifndef MODULES_DATA_WRITER_H_
#define MODULES_DATA_WRITER_H_

#include "common/vcu_status.h"

/**
 * @brief 同步can数据到总线(定时器周期性发送)
 *
 */
void Can_Msg_Sync(void);
/**
 * @brief 同步底盘状态
 *
 * @param status
 */
void Sync_Chassis_Status(const ChassisStatus *status);
/**
 * @brief 同步清扫指令
 *
 * @param cmd
 */
void Sync_Sweep_Cmd(const SweepCmd *cmd);
/**
 * @brief 同步电源指令
 *
 * @param cmd
 */
void Sync_Power_Cmd(const PowerCmd *cmd);
/**
 * @brief 同步驱动指令
 *
 * @param cmd
 */
void Sync_Drv_Cmd(const DrvCmd *cmd);
/**
 * @brief 同步转向指令
 *
 * @param steer
 */
void Sync_Str_Cmd(const SteerCmd *cmd);
#endif // MODULES_DATA_WRITER_H_
