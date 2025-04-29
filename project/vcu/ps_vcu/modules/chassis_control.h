/*
 * @Author: dding3
 * @Date: 2025-03-10 15:48:49
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-12 14:19:52
 * @Description:
 * @FilePath: \ps_vcu\modules\chassis_control.h
 */
#ifndef MODULES_CHASSIS_CONTROL_H_
#define MODULES_CHASSIS_CONTROL_H_

#include "common/vcu_status.h"

/**
 * @brief 底盘控制
 *
 * @param cmd
 */
void Chassis_Control(ChassisStatus *status, ChassisCmd *cmd);

/**
 * @brief 灯光闪烁逻辑(闪烁逻辑基于定时器实现)
 *
 */
void Lamp_Flash_Run(void);

#endif // MODULES_CHASSIS_CONTROL_H_
