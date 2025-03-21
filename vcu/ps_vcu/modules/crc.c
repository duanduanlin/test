/*
 * @Author: dding3
 * @Date: 2025-03-05 18:37:37
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-05 18:38:02
 * @Description:
 * @FilePath: \ps_vcu\modules\crc.c
 */
#include "modules/crc.h"

uint8_t Calculate_Crc(const uint8_t *data, int len)
{
    uint8_t result = 0;
    for (int i = 0; i < len; i++)
    {
        result ^= data[i];
    }

    return result;
}
