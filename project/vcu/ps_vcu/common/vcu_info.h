/*
 * @Author: dding3
 * @Date: 2025-03-05 17:54:25
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-28 16:08:10
 * @Description:
 * @FilePath: \ps_vcu\common\vcu_info.h
 */
#ifndef COMMON_VCU_INFO_H_
#define COMMON_VCU_INFO_H_

#define VCU_SOFT_VERSION_NUM (100)
#define VCU_HARD_VERSION_NUM (100)

/**
 * @brief 从flash中读取配置
 *
 * @param info
 * @return int
 */
int Vcu_Info_Read(void);

/**
 * @brief 写入配置到flash
 *
 * @param info
 * @return int
 */
int Vcu_Info_Write(void);

/**
 * @brief 获取里程信息
 *
 * @return double
 */
double Vcu_Info_GetOdometer(void);

/**
 * @brief 设置里程
 *
 * @param odometer
 */
void Vcu_Info_AddOdometer(double odometer);

#endif // COMMON_VCU_INFO_H_
