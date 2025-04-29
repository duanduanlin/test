/*
 * @Author: hanson
 * @Date: 2025-02-13 14:33:39
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-27 17:14:34
 * @Description:
 * 1.此模块通过usart1输出串口日志，有五个可设置的等级
 * 2.usart1默认已开启dma功能
 * @FilePath: \ps_vcu\modules\log.h
 */
#ifndef MODULES_LOG_H_
#define MODULES_LOG_H_

// 日志级别枚举
typedef enum
{
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_CRITICAL
} log_level_t;

/**
 * @brief 初始化日志模块
 *
 */
void Log_Init(void);

/**
 * @brief 销毁日志模块
 *
 */
void Log_Deinit(void);

/**
 * @brief 输出日志到串口
 *
 * @param format
 * @param ...
 */
void Log_Out(log_level_t lvl, const char *format, ...);

/**
 * @brief 设置日志等级
 *
 * @param lvl
 */
void Log_Set_Lvl(log_level_t lvl);

/**
 * @brief 存储日志
 *
 */
void Log_File_Sync(void);

/**
 * @brief 存储数据
 *
 */
void Log_Data_Sync(void);

/**
 * @brief 保存can数据
 *
 * @param buff
 * @param len
 */
void Log_Data_Save(const char *buff, int len);

/**
 * @brief 初始化logfile
 *
 */
void LogFile_Init(void);

/**
 * @brief 获取当前日志等级
 *
 * @return log_level_t
 */
log_level_t log_get_lvl(void);

#define LOG(level, ...)                  \
    do                                   \
    {                                    \
        if (level >= log_get_lvl())      \
        {                                \
            Log_Out(level, __VA_ARGS__); \
        }                                \
    } while (0)

#define LOG_EVERY(level, timeout, ...)             \
    do                                             \
    {                                              \
        static uint32_t last_tick = 0;             \
        if (level >= log_get_lvl() &&              \
            (HAL_GetTick() - last_tick > timeout)) \
        {                                          \
            last_tick = HAL_GetTick();             \
            Log_Out(level, __VA_ARGS__);           \
        }                                          \
    } while (0)

#define LOG_ERROR(...) LOG(LOG_LEVEL_ERROR, __VA_ARGS__)
#define LOG_WARN(...) LOG(LOG_LEVEL_WARNING, __VA_ARGS__)
#define LOG_INFO(...) LOG(LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_DEBUG(...) LOG(LOG_LEVEL_DEBUG, __VA_ARGS__)

#define LOG_EVERY_SECOND(...) LOG_EVERY(LOG_LEVEL_INFO, 1000, __VA_ARGS__)

#endif // MODULES_LOG_H_
