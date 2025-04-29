/*
 * @Author: hanson
 * @Date: 2025-02-13 14:35:36
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-02 11:28:27
 * @Description:
 * @FilePath: \ps_vcu\modules\log.c
 */
#include "modules/log.h"
#include "common/error_code.h"
#include "usart.h"
#include "rtc.h"
#include "cmsis_os.h"
#include "ringbuffer.h"
#include "sd_logfile.h"
#include <stdio.h>
#include <stdarg.h>

#define LOG_BUFF_LINE_SIZE (128)
#define LOG_MAX_NUM (64)

#define DATA_BUFF_LINE_SIZE (128)
#define DATA_MAX_NUM (1024)

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
static LogFileHandler s_logfileH;

static osMutexId_t s_datasave_mutex_id;
const osMutexAttr_t DataSave_Mutex_attr = {
    "datasaveMutex",    // human readable mutex name
    osMutexPrioInherit, // attr_bits
    NULL,               // memory for control block
    0U                  // size for control block
};

static char s_data_buff_ring[DATA_MAX_NUM * DATA_BUFF_LINE_SIZE]; // ring buffer 缓存
static ring_buffer_t s_ring_buffer_data;
static LogFileHandler s_datafileH;

static int s_log_file_init = 0;

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
        printf("log buffer full\r\n");
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

    s_datasave_mutex_id = osMutexNew(&DataSave_Mutex_attr);
    ring_buffer_init(&s_ring_buffer_data, s_data_buff_ring, DATA_MAX_NUM * DATA_BUFF_LINE_SIZE);
}

void Log_Deinit(void)
{
    // todo
}

void Log_Out(log_level_t lvl, const char *format, ...)
{
    uint16_t len = 0;
    osMutexAcquire(s_logout_mutex_id, osWaitForever);
    len = RTC_GetTimestampsStr((char *)s_log_buff_line, LOG_BUFF_LINE_SIZE);
    va_list args;
    va_start(args, format);
    len += vsnprintf((char *)s_log_buff_line + len, LOG_BUFF_LINE_SIZE - len, (char *)format, args);
    va_end(args);
    log_buff_push(s_log_buff_line, len);
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

void Log_File_Sync(void)
{
    int len = 0;
    uint8_t buffer[LOG_BUFF_LINE_SIZE] = {0};
    if(s_log_file_init == 0)
    {
        printf("log file is not init\r\n");
        return;
    }
    while ((len = ring_buffer_dequeue_arr(&s_ring_buffer_log, (char *)&buffer, sizeof(buffer))) != 0)
    {
        // USART1_Transmit_DMA(buffer, len);
        LogFile_Write(&s_logfileH, (char *)buffer, len);
    }
}

void Log_Data_Save(const char *buff, int len)
{
    // if (!ring_buffer_is_full(&s_ring_buffer_data))
    // {
    //     ring_buffer_queue_arr(&s_ring_buffer_data, (char *)buff, len);
    // }
    // else
    // {
    //     printf("data buffer full\r\n");
    // }
}

void Log_Data_Sync(void)
{
    int len = 0;
    uint8_t buffer[DATA_BUFF_LINE_SIZE] = {0};
    int len_total = 0;
    if(s_log_file_init == 0)
    {
        printf("data file is not init\r\n");
        return;
    }
    while ((len = ring_buffer_dequeue_arr(&s_ring_buffer_data, (char *)&buffer, sizeof(buffer))) != 0)
    {
        // USART1_Transmit_DMA(buffer, len);
        // LogFile_Write(&s_datafileH, (char *)buffer, len);
        len_total += len;
    }

    // printf("save data %d\r\n", len_total);
}

void LogFile_Init(void)
{
    if (s_log_file_init == 0)
    {
        LogFile_Scan_Dir();

        sprintf(s_logfileH.path, "%s", "log");
        s_logfileH.name_pattern = LOG_FILE_NAME_PARTTERN;
        // LogFile_Clean(&s_logfileH);
        LogFile_Scan_File(&s_logfileH);
        LogFile_New(&s_logfileH);

        sprintf(s_datafileH.path, "%s", "data");
        s_datafileH.first_line = DATA_FILE_FIRST_LINE;
        s_datafileH.name_pattern = DATA_FILE_NAME_PARTTERN;
        // LogFile_Clean(&s_datafileH);
        LogFile_Scan_File(&s_datafileH);
        LogFile_New(&s_datafileH);
        s_log_file_init = 1;
    }
}
