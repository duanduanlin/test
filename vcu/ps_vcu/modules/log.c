/*
 * @Author: hanson
 * @Date: 2025-02-13 14:35:36
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-21 15:28:47
 * @Description:
 * @FilePath: \ps_vcu\modules\log.c
 */
#include "modules/log.h"
#include "common/error_code.h"
#include "usart.h"
#include "rtc.h"
#include "cmsis_os.h"
#include "ringbuffer.h"
#include <stdio.h>
#include <stdarg.h>

#define LOG_BUFF_LINE_SIZE (128)
#define LOG_MAX_NUM (64)

static osMutexId_t s_logout_mutex_id;
const osMutexAttr_t Logout_Mutex_attr = {
    "logoutMutex",      // human readable mutex name
    osMutexPrioInherit, // attr_bits
    NULL,               // memory for control block
    0U                  // size for control block
};

static uint8_t s_log_buff_line[LOG_BUFF_LINE_SIZE]; // 行缓存
static log_level_t s_log_lvl = LOG_LEVEL_DEBUG;

static char s_log_buff_ring[LOG_MAX_NUM * LOG_BUFF_LINE_SIZE]; // ring buffer 缓存
static ring_buffer_t s_ring_buffer_log;

static int log_buff_push(uint8_t *buff, int len)
{
    int ret = VCU_FAILED;
    if (buff == NULL)
    {
        return ret;
    }

    if (!ring_buffer_is_full(&s_ring_buffer_log))
    {
        ring_buffer_queue_arr(&s_ring_buffer_log, (char *)buff, len);
        ret = VCU_OK;
    }
    else
    {
        LOG_ERROR("log buffer full\r\n");
    }

    return ret;
}

// 重定义fputc函数
int fputc(int ch, FILE *f)
{
    // osMutexAcquire(s_logout_mutex_id, osWaitForever);
    USART1_Transmit_DMA((uint8_t *)&ch, 1);
    // osMutexRelease(s_logout_mutex_id);
    return ch;
}

void Log_Init(void)
{
    // todo
    s_logout_mutex_id = osMutexNew(&Logout_Mutex_attr);
    ring_buffer_init(&s_ring_buffer_log, s_log_buff_ring, LOG_MAX_NUM * LOG_BUFF_LINE_SIZE);
}

void Log_Deinit(void)
{
    // todo
}

void Log_Out(log_level_t lvl, const char *format, ...)
{
    uint16_t len = 0;
    osMutexAcquire(s_logout_mutex_id, osWaitForever);
    len = RTC_GetTimestamps((char *)s_log_buff_line, LOG_BUFF_LINE_SIZE);
    va_list args;
    va_start(args, format);
    len += vsnprintf((char *)s_log_buff_line + len, LOG_BUFF_LINE_SIZE - len, (char *)format, args);
    va_end(args);
    // log_buff_push(s_log_buff_line, len);
    USART1_Transmit_DMA(s_log_buff_line, len);
    osMutexRelease(s_logout_mutex_id);
}

void Log_Set_Lvl(log_level_t lvl)
{
    s_log_lvl = lvl;
}

log_level_t log_get_lvl(void)
{
    return s_log_lvl;
}

void Log_Save(void)
{
    int len = 0;
    uint8_t buffer[LOG_BUFF_LINE_SIZE] = {0};
    while ((len = ring_buffer_dequeue_arr(&s_ring_buffer_log, (char *)&buffer, sizeof(buffer))) != 0)
    {
        USART1_Transmit_DMA(buffer, len);
    }
}
