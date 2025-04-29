/*
 * @Author: dding3
 * @Date: 2025-03-14 09:53:28
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-24 14:25:52
 * @Description:
 * @FilePath: \ps_vcu\modules\data_handle.c
 */
#include "common/error_code.h"
#include "modules/log.h"
#include "modules/data_handle.h"
#include "ringbuffer.h"
#include "cmsis_os.h"
#include "usart.h"
#include "rtc.h"
#include "stdio.h"

#define CAN_ID_MAX_NUM (128)
#define CAN_MSG_BUFF_SIZE (128)

#define UART_BUFFER_SIZE (128)

// ring buff
static char s_recv_buff[CAN_MSG_BUFF_SIZE * sizeof(CanMsg)];
static ring_buffer_t s_ring_buffer_recv;

static char s_uart1_buff[UART_BUFFER_SIZE];
static ring_buffer_t s_ring_buffer_uart1;

static char s_send_buff_a[CAN_MSG_BUFF_SIZE * sizeof(CanMsg)];
static ring_buffer_t s_ring_buffer_send_a;

static char s_send_buff_c[CAN_MSG_BUFF_SIZE * sizeof(CanMsg)];
static ring_buffer_t s_ring_buffer_send_c;

static osMutexId_t s_recv_mutex_id;
const osMutexAttr_t Recv_Mutex_attr = {
    "recvMutex",        // human readable mutex name
    osMutexPrioInherit, // attr_bits
    NULL,               // memory for control block
    0U                  // size for control block
};

static osMutexId_t s_send_mutex_id;
const osMutexAttr_t Send_Mutex_attr = {
    "sendMutex",        // human readable mutex name
    osMutexPrioInherit, // attr_bits
    NULL,               // memory for control block
    0U                  // size for control block
};

static int can_msg_push(CanMsg *msg)
{
    int ret = VCU_FAILED;
    if (msg == NULL)
    {
        return ret;
    }

    if (!ring_buffer_is_full(&s_ring_buffer_recv))
    {
        osMutexAcquire(s_recv_mutex_id, osWaitForever);
        ring_buffer_queue_arr(&s_ring_buffer_recv, (char *)msg, sizeof(CanMsg));
        osMutexRelease(s_recv_mutex_id);
        ret = VCU_OK;
    }
    else
    {
        LOG_ERROR("msg buffer full\r\n");
    }

    return ret;
}

static int can_msg_cb_a(CanMsg *msg)
{
    can_msg_push(msg);
    return VCU_OK;
}

static int can_msg_cb_c(CanMsg *msg)
{
    can_msg_push(msg);
    return VCU_OK;
}

int uart1_data_cb(uint8_t *buff, int len)
{
    int ret = VCU_FAILED;
    if (!ring_buffer_is_full(&s_ring_buffer_uart1))
    {
        ring_buffer_queue_arr(&s_ring_buffer_uart1, (char *)buff, len);
        ret = VCU_OK;
    }
    return ret;
}

void Data_Handle_Parse(DataReader *reader)
{
    CanMsg msg = {0};
    char uart_data[UART_BUFFER_SIZE] = {0};
    while (ring_buffer_dequeue_arr(&s_ring_buffer_recv, (char *)&msg, sizeof(CanMsg)) != 0)
    {
        char tmp[128] = {0};
        int len = FDCAN_Msg2CSV(&msg, "R", tmp, 128);
        // int len = snprintf(tmp, 128, "%u,%s,%x,%x %x %x %x %x %x %x %x\r\n", RTC_GetTimestamps(), "R", msg.id, msg.buffer[0], msg.buffer[1], msg.buffer[2], msg.buffer[3], msg.buffer[4], msg.buffer[5], msg.buffer[6], msg.buffer[7]);
        Log_Data_Save(tmp, len);
        LOG_INFO("[%d] R:%x\r\n", HAL_GetTick(), msg.id);
        Can_Msg_Parse(&msg, reader);
    }
    while (ring_buffer_dequeue_arr(&s_ring_buffer_uart1, (char *)&uart_data, UART_BUFFER_SIZE) != 0)
    {
        LOG_INFO("uart R:%s\r\n", uart_data);
    }
}

int Data_Handle_Write(CanNet net, CanMsg *msg)
{
    int ret = VCU_FAILED;
    osMutexAcquire(s_send_mutex_id, osWaitForever);
    if (net == CanNetA)
    {
        if (!ring_buffer_is_full(&s_ring_buffer_send_a))
        {
            ring_buffer_queue_arr(&s_ring_buffer_send_a, (char *)msg, sizeof(CanMsg));
            ret = VCU_OK;
        }
    }
    else
    {
        if (!ring_buffer_is_full(&s_ring_buffer_send_c))
        {
            ring_buffer_queue_arr(&s_ring_buffer_send_c, (char *)msg, sizeof(CanMsg));
            ret = VCU_OK;
        }
    }
    osMutexRelease(s_send_mutex_id);
    return ret;
}

void Data_Handle_Sync(void)
{
    CanMsg msg = {0};
    while (ring_buffer_dequeue_arr(&s_ring_buffer_send_c, (char *)&msg, sizeof(CanMsg)) != 0)
    {
        FDCAN2_Send_Msg(&msg);
        char tmp[128] = {0};
        int len = FDCAN_Msg2CSV(&msg, "T", tmp, 128);
        Log_Data_Save(tmp, len);
    }
    while (ring_buffer_dequeue_arr(&s_ring_buffer_send_a, (char *)&msg, sizeof(CanMsg)) != 0)
    {
        FDCAN1_Send_Msg(&msg);
        char tmp[128] = {0};
        int len = FDCAN_Msg2CSV(&msg, "T", tmp, 128);
        Log_Data_Save(tmp, len);
    }
}

void Data_Handle_Init(void)
{
    uint32_t ids[CAN_ID_MAX_NUM] = {0};
    int len = 0;

    // 注册数据回调
    FDCAN1_Set_RecvMsgCB(can_msg_cb_a);
    FDCAN2_Set_RecvMsgCB(can_msg_cb_c);

    USART1_Set_RecvCB(uart1_data_cb);

    // 初始化环形数组
    s_recv_mutex_id = osMutexNew(&Recv_Mutex_attr);
    ring_buffer_init(&s_ring_buffer_recv, s_recv_buff, CAN_MSG_BUFF_SIZE * sizeof(CanMsg));
    ring_buffer_init(&s_ring_buffer_uart1, s_uart1_buff, UART_BUFFER_SIZE);

    s_send_mutex_id = osMutexNew(&Send_Mutex_attr);
    ring_buffer_init(&s_ring_buffer_send_a, s_send_buff_a, CAN_MSG_BUFF_SIZE * sizeof(CanMsg));
    ring_buffer_init(&s_ring_buffer_send_c, s_send_buff_c, CAN_MSG_BUFF_SIZE * sizeof(CanMsg));

    // 设置can过滤
    len = Can_Msg_GetIds(CanNetA, ids, CAN_ID_MAX_NUM);
    FDCAN1_RX_Filter(ids, len);

    len = Can_Msg_GetIds(CanNetC, ids, CAN_ID_MAX_NUM);
    FDCAN2_RX_Filter(ids, len);

    // 启动can
    FDCAN1_Start();
    FDCAN2_Start();
}
