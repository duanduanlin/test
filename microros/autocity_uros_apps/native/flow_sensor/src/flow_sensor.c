/*
 * @Author: hanson
 * @Date: 2024-11-13 16:27:57
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-11 14:11:01
 * @Description:
 * @FilePath: \autocity_uros_apps\native\flow_sensor\src\flow_sensor.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <modbus/modbus.h>
#include <errno.h>
#include "flow_sensor.h"

static modbus_t *ctx = NULL;

int flow_sensor_init(const char *dev, int bitrates)
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
    modbus_set_slave(ctx, 1);

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

int flow_sensor_deinit()
{
    // 关闭Modbus连接
    modbus_close(ctx);
    modbus_free(ctx);
}

float flow_sensor_read_flow_value()
{
    uint16_t tab_reg[64];
    int rc;

    if (ctx == NULL)
    {
        fprintf(stderr, "ctx == NULL\n");
        return 0;
    }

    // 读取Modbus寄存器
    rc = modbus_read_registers(ctx, 0x9, 3, tab_reg);
    if (rc == -1)
    {

        fprintf(stderr, "无法读取Modbus寄存器: %s\n", modbus_strerror(errno));
        return 0;
        // exit(1);
    }

    printf("从Modbus RTU从机读取的瞬时流量是：%d %d %d,rc:%d\n", tab_reg[0], tab_reg[1], tab_reg[2], rc);

    return (tab_reg[0] << 16 + tab_reg[1]) + tab_reg[2] / 100.0;
}

float flow_sensor_read_total_flow_value()
{
    uint16_t tab_reg[64];
    int rc;

    if (ctx == NULL)
    {
        fprintf(stderr, "ctx == NULL\n");
        return 0;
    }

    // 读取Modbus寄存器
    rc = modbus_read_registers(ctx, 0xc, 3, tab_reg);
    if (rc == -1)
    {

        fprintf(stderr, "无法读取Modbus寄存器: %s\n", modbus_strerror(errno));
        return 0;
        // exit(1);
    }

    printf("从Modbus RTU从机读取的总流量是：%d %d %d,rc:%d\n", tab_reg[0], tab_reg[1], tab_reg[2], rc);

    return (tab_reg[0] << 16 + tab_reg[1]) + tab_reg[2] / 100.0;
}
