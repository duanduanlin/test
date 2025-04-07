/*
 * @Author: hanson
 * @Date: 2024-11-13 16:27:57
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-16 14:43:56
 * @Description:
 * @FilePath: \autocity_uros_apps\native\modbus\src\modbus_dev.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <modbus/modbus.h>
#include <errno.h>
#include <string.h>
#include "modbus_dev.h"

#define MAX_REG_DATA_LEN (64)

static modbus_t *ctx = NULL;

int modbus_dev_init(const char *dev, int bitrates, int add)
{
    // 创建Modbus RTU主机上下文
    ctx = modbus_new_rtu(dev, bitrates, 'N', 8, 1);
    if (ctx == NULL)
    {

        fprintf(stderr, "无法创建Modbus RTU主机上下文\n");
        return -1;
        // exit(1);
    }

    // 设置Modbus主机从机地址
    modbus_set_slave(ctx, add);

    // 打开Modbus RTU连接
    if (modbus_connect(ctx) == -1)
    {

        fprintf(stderr, "无法连接到Modbus RTU从机: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        ctx = NULL;
        return -1;
        // exit(1);
    }

    return 0;
}

int modbus_dev_deinit()
{
    // 关闭Modbus连接
    modbus_close(ctx);
    modbus_free(ctx);
}

int modbus_dev_read_registers(int add, int len, uint16_t *data)
{
    uint16_t tab_reg[MAX_REG_DATA_LEN];
    int rc;

    if (ctx == NULL)
    {
        fprintf(stderr, "ctx == NULL\n");
        return -1;
    }

    // if (len > MAX_REG_DATA_LEN)
    // {
    //     fprintf(stderr, "invalid len\n");
    //     return -1;
    // }

    // 读取Modbus寄存器
    rc = modbus_read_registers(ctx, add, len, tab_reg);
    if (rc == -1)
    {

        fprintf(stderr, "无法读取Modbus寄存器: %s\n", modbus_strerror(errno));
        return -1;
    }

    printf("tab_reg:");

    for (int i = 0; i < rc; i++)
    {
        printf("0x%x ", tab_reg[i]);
        data[i] = tab_reg[i];
    }

    printf("\r\n");

    // memcpy(data, tab_reg, rc);

    return rc;
}
