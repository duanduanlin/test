/*
 * @Author: dding3
 * @Date: 2025-03-14 09:53:28
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-14 14:11:37
 * @Description:
 * @FilePath: \ps_vcu\modules\data_handle.c
 */
#include "common/error_code.h"
#include "modules/log.h"
#include "modules/data_handle.h"
#include "ringbuffer.h"
#include "cmsis_os.h"

#define CAN_ID_MAX_NUM (128)
#define CAN_MSG_BUFF_SIZE (128)

// ring buff
static char s_msg_buff[CAN_MSG_BUFF_SIZE * sizeof(CanMsg)];
static ring_buffer_t s_ring_buffer_msg;

static osMutexId_t s_rb_mutex_id;
const osMutexAttr_t Rb_Mutex_attr = {
    "rbMutex",          // human readable mutex name
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

    if (!ring_buffer_is_full(&s_ring_buffer_msg))
    {
        osMutexAcquire(s_rb_mutex_id, osWaitForever);
        ring_buffer_queue_arr(&s_ring_buffer_msg, (char *)msg, sizeof(CanMsg));
        osMutexRelease(s_rb_mutex_id);
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

void Data_Handle_Parse(DataReader *reader)
{
    CanMsg msg = {0};
    while (ring_buffer_dequeue_arr(&s_ring_buffer_msg, (char *)&msg, sizeof(CanMsg)) != 0)
    {
        LOG_INFO("[%d] R:%x\r\n", HAL_GetTick(),msg.id);
        Can_Msg_Parse(&msg, reader);
    }
}

void Data_Handle_Init(void)
{
    uint32_t ids[CAN_ID_MAX_NUM] = {0};
    int len = 0;

    //注册数据回调
    FDCAN1_Set_RecvMsgCB(can_msg_cb_a);
    FDCAN2_Set_RecvMsgCB(can_msg_cb_c);

    //初始化环形数组
    s_rb_mutex_id = osMutexNew(&Rb_Mutex_attr);
    ring_buffer_init(&s_ring_buffer_msg, s_msg_buff, CAN_MSG_BUFF_SIZE * sizeof(CanMsg));

    // 设置can过滤
    len = Can_Msg_GetIds(CanNetA, ids, CAN_ID_MAX_NUM);
    FDCAN1_RX_Filter(ids, len);

    len = Can_Msg_GetIds(CanNetC, ids, CAN_ID_MAX_NUM);
    FDCAN2_RX_Filter(ids, len);

    //启动can
    FDCAN1_Start();
    FDCAN2_Start();
}
