/*
 * @Author: dding3
 * @Date: 2025-03-05 18:35:59
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-05 18:38:45
 * @Description:
 * @FilePath: \ps_vcu\modules\crc.h
 */
#ifndef MODULES_CRC_H_
#define MODULES_CRC_H_
#include <stdint.h>
/**
 * @brief 计算CRC
 * 全部数据异或计算
 * @param data
 * @param len
 * @return uint8_t
 */
uint8_t Calculate_Crc(const uint8_t *data, int len);
#endif // MODULES_CRC_H_
