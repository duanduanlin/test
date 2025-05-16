#include "com.h"
#include "app.h"

// scp消息头
#define SCP_MAGIC0 0x43
#define SCP_MAGIC1 0x54
#define SCP_MAGIC2 0x52
#define SCP_MAGIC3 0x4C

#define UART_MSG_RX_BUF_SIZE 1024

static scp_parser_t scp_parser;
static uint8_t uart_msg_rx_buf[UART_MSG_RX_BUF_SIZE];

void serial_parse_init(void)
{
    scp_parser.state = Parse_Magic0;
    scp_parser.content_cnt = 0;
    scp_parser.max_interval_ms = 100;
    scp_parser.time_start_ms = 0;
    scp_parser.msg = (scp_msg_t *)uart_msg_rx_buf;
    // scp_parser.get_time_ms = HAL_GetTick;
    scp_parser.get_time_ms = sys_ops_api->get_sys_tick;
    scp_parser.callback = app_ota_msg_handler;
}

void serial_msg_parse(uint8_t data)
{
    uint16_t crc16_calc;

    if (scp_parser.get_time_ms() - scp_parser.time_start_ms > scp_parser.max_interval_ms)
    {
        scp_parser.state = Parse_Magic0;
        scp_parser.content_cnt = 0;
    }

    switch (scp_parser.state)
    {
    case Parse_Magic0:
        if (data == SCP_MAGIC0)
        {
            scp_parser.state = Parse_Magic1;
            scp_parser.msg->magic0 = data;
            scp_parser.time_start_ms = scp_parser.get_time_ms();
        }
        break;

    case Parse_Magic1:
        if (data == SCP_MAGIC1)
        {
            scp_parser.state = Parse_Magic2;
            scp_parser.msg->magic1 = data;
            scp_parser.time_start_ms = scp_parser.get_time_ms();
        }
        else
        {
            scp_parser.state = Parse_Magic0;
        }
        break;

    case Parse_Magic2:
        if (data == SCP_MAGIC2)
        {
            scp_parser.state = Parse_Magic3;
            scp_parser.msg->magic2 = data;
            scp_parser.time_start_ms = scp_parser.get_time_ms();
        }
        else
        {
            scp_parser.state = Parse_Magic0;
        }
        break;

    case Parse_Magic3:
        if (data == SCP_MAGIC3)
        {
            scp_parser.state = Parse_Cmd;
            scp_parser.msg->magic3 = data;
            scp_parser.time_start_ms = scp_parser.get_time_ms();
        }
        else
        {
            scp_parser.state = Parse_Magic0;
        }
        break;

    case Parse_Cmd:
        scp_parser.state = Parse_Cmd_Length_L;
        scp_parser.msg->cmd = data;
        scp_parser.time_start_ms = scp_parser.get_time_ms();
        break;

    case Parse_Cmd_Length_L:
        scp_parser.state = Parse_Cmd_Length_H;
        scp_parser.msg->cmd_length = data;
        scp_parser.time_start_ms = scp_parser.get_time_ms();
        break;

    case Parse_Cmd_Length_H:
        scp_parser.state = Parse_Content;
        scp_parser.msg->cmd_length |= (data << 8);
        scp_parser.time_start_ms = scp_parser.get_time_ms();
        break;

    case Parse_Content:
        scp_parser.msg->content[scp_parser.content_cnt++] = data;
        scp_parser.time_start_ms = scp_parser.get_time_ms();
        if ((scp_parser.content_cnt + 7) == scp_parser.msg->cmd_length)
        {
            scp_parser.state = Parser_Checksum_L;
        }
        break;

    case Parser_Checksum_L:
        scp_parser.state = Parser_Checksum_H;
        scp_parser.msg->checksum = data;
        scp_parser.time_start_ms = scp_parser.get_time_ms();
        break;

    case Parser_Checksum_H:
        scp_parser.state = Parse_Magic0;
        scp_parser.msg->checksum |= (data << 8);
        scp_parser.content_cnt = 0;
        scp_parser.time_start_ms = scp_parser.get_time_ms();
        crc16_calc = calc_crc_ccitt((uint8_t *)scp_parser.msg, scp_parser.msg->cmd_length);
        if (scp_parser.msg->checksum == crc16_calc)
        {
            scp_parser.callback(scp_parser.msg->cmd, scp_parser.msg->content, scp_parser.msg->cmd_length - 7);
        }
        break;

    default:
        scp_parser.state = Parse_Magic0;
        break;
    }
}

uint16_t scp_msg_pack(uint8_t *msg_buf, uint8_t cmd, uint8_t *content, uint16_t cmd_length)
{
    uint8_t i;
    uint16_t crc16_calc;
    // uint8_t *checksum;
    scp_msg_t *scp_msg = (scp_msg_t *)msg_buf;

    scp_msg->magic0 = SCP_MAGIC0;
    scp_msg->magic1 = SCP_MAGIC1;
    scp_msg->magic2 = SCP_MAGIC2;
    scp_msg->magic3 = SCP_MAGIC3;

    scp_msg->cmd = cmd;
    scp_msg->cmd_length = cmd_length + 7;

    for (i = 0; i < cmd_length; i++)
    {
        scp_msg->content[i] = content[i];
    }

    // checksum = &scp_msg->content[cmd_length];
    crc16_calc = calc_crc_ccitt((uint8_t *)scp_msg, scp_msg->cmd_length);
    memcpy(&scp_msg->content[cmd_length], &crc16_calc, sizeof(crc16_calc));

    return (scp_msg->cmd_length + 2);
}

uint16_t uavcan_msg_pack(uint8_t *msg_buf, uint8_t cmd, uint8_t *content, uint16_t cmd_length)
{
    msg_buf[0] = cmd;
    msg_buf[1] = 0;
    memcpy(&msg_buf[2], content, cmd_length);

    return (cmd_length + 2);
}
