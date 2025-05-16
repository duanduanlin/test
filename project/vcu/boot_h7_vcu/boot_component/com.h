#ifndef __COM_H__
#define __COM_H__

#include "port_canard.h"
#include <stdbool.h>
#include <stdint.h>

#define FW_UPGRADE_NORMAL 0x00
#define FW_UPGRADE_START 0x01
#define FW_UPGRADING 0x02
#define FW_UPGRADE_END 0x03
#define FW_UPGRADE_WRITTEN 0x04
#define FW_UPGRADE_IN_BOOT 0x05
#define FW_UPGRADE_MAX 0x06

// content最大长度
#define SCP_CONTENT_MAX_LEN 512 // 可根据具体应用修改-512

// 公共命令定义
#define SCP_CMD_200_UPGRADE_NOTHFY 0xC8
#define SCP_CMD_201_UPGRADE_VERIFY 0xC9
#define SCP_CMD_202_UPGRADE_PERMIT 0xCA
#define SCP_CMD_203_UPGRADE_FW_BLOCK 0xCB
#define SCP_CMD_204_UPGRADE_FW_BLOCK_ACK 0xCD
#define SCP_CMD_205_REBOOT 0xCE
#define SCP_CMD_206_UPGRADE_END 0xCF
#define SCP_CMD_209_VERSION_CHECK 0xD1
#define SCP_CMD_210_VERSION_CHECK_ACK 0xD2
#define SCP_CMD_211_UPGRADE_STATUS 0xD3

typedef struct __attribute__((packed))
{
    uint8_t magic0;
    uint8_t magic1;
    uint8_t magic2;
    uint8_t magic3;
    uint8_t cmd;
    uint16_t cmd_length;
    uint8_t content[SCP_CONTENT_MAX_LEN];

    uint16_t checksum;
} scp_msg_t;

typedef struct
{
    enum
    {
        Parse_Magic0,
        Parse_Magic1,
        Parse_Magic2,
        Parse_Magic3,
        Parse_Cmd,
        Parse_Cmd_Length_L,
        Parse_Cmd_Length_H,
        Parse_Content,
        Parser_Checksum_L,
        Parser_Checksum_H
    } state;

    uint16_t content_cnt;
    uint32_t time_start_ms;
    uint16_t max_interval_ms;

    scp_msg_t *msg;
    ;

    uint32_t (*get_time_ms)(void);
    void (*callback)(uint8_t, uint8_t *, uint16_t);
} scp_parser_t;

void serial_parse_init(void);
void serial_msg_parse(uint8_t data);
uint16_t scp_msg_pack(uint8_t *msg_buf, uint8_t cmd, uint8_t *content, uint16_t cmd_length);
uint16_t uavcan_msg_pack(uint8_t *msg_buf, uint8_t cmd, uint8_t *content, uint16_t cmd_length);

#endif /* __COM_H__ */
