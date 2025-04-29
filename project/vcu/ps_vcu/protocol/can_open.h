/*
 * @Author: dding3
 * @Date: 2025-04-22 14:54:34
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-23 14:59:54
 * @Description:
 * @FilePath: \ps_vcu\protocol\can_open.h
 */
#ifndef PROTOCOL_CAN_OPEN_H_
#define PROTOCOL_CAN_OPEN_H_

#include "stdint.h"

#define CAN_OPEN_NMT_CTRL_FRAME_ID (0x0)
#define CAN_OPEN_NMT_BOOT_UP_FRAME_ID (0x700 + 0x1)

#define CAN_OPEN_SDO_CLIENT_NODE_1_FRAME_ID (0x600 + 0x1)
#define CAN_OPEN_SDO_SERVER_NODE_1_FRAME_ID (0x580 + 0x1)

#define CAN_OPEN_PDO_RX_1_FRAME_ID (0x200 + 0x1)
#define CAN_OPEN_PDO_TX_1_FRAME_ID (0x180 + 0x1)

typedef enum nmt_cmd
{
    NMT_CMD_START = 0x01,      // 启动
    NMT_CMD_STOP = 0x02,       // 停止
    NMT_CMD_PRE_FUNC = 0x80,   // 预操作
    NMT_CMD_NODE_RESET = 0x81, // 节点复位
    NMT_CMD_COMM_RESET = 0x82, // 通信复位
} NMT_CMD;

typedef enum node_id
{
    NODE_ID_ALL = 0x0, // 全部节点
    NODE_ID_1 = 0x1,   // 节点1
} NODE_ID;

typedef struct
{
    uint8_t s : 1;         // 是否确认长度，0不确定，1确定
    uint8_t e : 1;         // 传输方式，0正常，1表示快速
    uint8_t n : 2;         // 无意义数据字节数
    uint8_t reserved : 1;  // 保留默认0
    uint8_t reserved1 : 1; // 默认1
    uint8_t d : 1;         // 方向 0 client,1 server
    uint8_t reserved2 : 1; // 保留默认0
} SDO_CMD;

typedef enum
{
    OD_CTRL_CMD_READY = 0x6,  // 就绪
    OD_CTRL_CMD_START = 0x7,  // 启动
    OD_CTRL_CMD_ENABLE = 0xF, // 电机使能
    OD_CTRL_CMD_RM = 0x4F,    // 相对运动
    OD_CTRL_CMD_RM_CN = 0x5F, // 相对运动控制使能
    OD_CTRL_CMD_AM_CN = 0x1F, // 绝对运动控制使能
} OD_CTRL_CMD;                // 控制字命令

typedef enum
{
    OD_MODE_PP = 0x1, // 位置
    OD_MODE_PV = 0x2, // 速度
    OD_MODE_PT = 0x3, // 扭矩
    OD_MODE_HM = 0x4, // 原点
} OD_MODE;            // 控制字命令

typedef enum
{
    OD_RUN_DIR_ALL_P = 0x0,  // 所有模式正转
    OD_RUN_DIR_PP_N = 0x80,  // pp和hm模式反转
    OD_RUN_DIR_PV_N = 0x40,  // pv模式反转
    OD_RUN_DIR_PT_N = 0x20,  // pt模式反转
    OD_RUN_DIR_ALL_N = 0xE0, // 所有模式反转
} OD_RUN_DIR;                // 运转方向

typedef enum od_id
{
    OD_ID_CTRL_REQ = 0x6040,    // 控制字
    OD_ID_CTRL_RES = 0x6041,    // 状态字
    OD_ID_MODE_REQ = 0x6060,    // 模式选择
    OD_ID_MODE_RES = 0x6061,    // 模式状态
    OD_ID_MAP_RES = 0x6063,     // 电机绝对位置反馈
    OD_ID_UAP_RES = 0x6064,     // 用户绝对位置反馈
    OD_ID_TAP_REQ = 0x607A,     // 设置位置
    OD_ID_RUN_DIR_REQ = 0x607E, // 运转方向
} OD_ID;                        // 对象字典id

/**
 * @brief 打包nmt控制命令
 *
 * @param data 组包后的数据
 * @param cmd nmt命令
 * @param id 节点id
 * @return int 成功返回0，失败返回-1
 */
int Can_Open_Pack_NMT(uint8_t *data, uint8_t cmd, NODE_ID id);

/**
 * @brief
 *
 * @param data 组包后的数据
 * @param cmd sdo命令
 * @param odi 对象字典索引
 * @param sodi 对象字典子索引
 * @param data 参数
 * @return int
 */
int Can_Open_Pack_SDO(uint8_t *buffer, uint8_t cmd, uint16_t odi, uint8_t sodi, uint8_t data[4]);

/**
 * @brief 处理nmt协议
 *
 * @param data 数据
 * @return int
 */
int Can_Open_Handle_NMT_BootUp(const uint8_t *data);

/**
 * @brief sdo server协议处理
 *
 * @param data
 * @return int
 */
int Can_Open_Handle_SDO_Server(const uint8_t *data);

/**
 * @brief canoepn协议处理
 *
 * @return int
 */
int Can_Open_Sync(void);

#endif // PROTOCOL_CAN_OPEN_H_
