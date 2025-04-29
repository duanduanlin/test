/*
 * @Author: dding3
 * @Date: 2025-04-22 16:56:04
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-23 16:18:29
 * @Description:
 * @FilePath: \ps_vcu\protocol\can_open.c
 */
#include "stdio.h"
#include "protocol/can_open.h"

typedef enum
{
    RunState_INIT = 0x0,    // 初始状态
    RunState_Start = 0x1,   // 启动状态
    RunState_Running = 0x2, // 运行状态
    RunState_Stop = 0x3,    // 停止状态
} RunState;

static struct
{
    RunState state;
} s_run_status;

int Can_Open_Pack_NMT(uint8_t *data, uint8_t cmd, NODE_ID id)
{
    int ret = -1;
    if (data != NULL)
    {
        data[0] = cmd & 0xFF;
        data[1] = id;
        ret = 0;
    }

    return ret;
}

int Can_Open_Pack_SDO(uint8_t *buffer, uint8_t cmd, uint16_t obi, uint8_t sobi, uint8_t data[4])
{
    int ret = -1;
    if (data != NULL)
    {
        buffer[0] = cmd & 0xFF;
        buffer[1] = obi & 0xFF;
        buffer[2] = (obi >> 8) & 0xFF;
        buffer[3] = sobi & 0xFF;
        buffer[4] = data[0];
        buffer[5] = data[1];
        buffer[6] = data[2];
        buffer[7] = data[3];
        ret = 0;
    }

    return ret;
}

int Can_Open_Handle_NMT_BootUp(const uint8_t *data)
{
    int ret = -1;
    return ret;
}

int Can_Open_Handle_SDO_Server(const uint8_t *data)
{
    int ret = -1;
    return ret;
}

int Can_Open_Sync(void)
{
    // 此函数10ms执行一次，需要做状态机管理
    switch (s_run_status.state)
    {
    case RunState_INIT:
        break;
    case RunState_Start:
        break;
    case RunState_Running:
        break;
    case RunState_Stop:
        break;
    }
    return 0;
}
