/*
 * @Author: dding3
 * @Date: 2025-03-27 10:37:30
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-31 10:29:44
 * @Description:
 * @FilePath: \ps_vcu\packages\sd_driver\sd_logfile.h
 */
#ifndef PACKAGES_SD_DRIVER_SD_LOGFILE_H_
#define PACKAGES_SD_DRIVER_SD_LOGFILE_H_

#include "fatfs.h"

#define FILE_NAME_LEN_MAX (32)
#define LOG_FILE_MAX_SIZE (20 * 1024 * 1024)
#define LOG_FILE_SAVE_TIME (7*24*60*60)
#define LOG_FILE_NAME_PARTTERN ("vcu-%u.log")
#define DATA_FILE_NAME_PARTTERN ("can-%u.csv")

#define DATA_FILE_FIRST_LINE ("TIME,TX/RX,ID(HEX),DATA(HEX)\r\n")

typedef struct log_file_handler
{
    long timestamps_last;             // 最新的时间戳
    char name[FILE_NAME_LEN_MAX];     // 当前日志文件名
    char path[FILE_NAME_LEN_MAX];     // 当前路径
    char *name_pattern;               // 命名模式
    char filePath[FILE_NAME_LEN_MAX]; // 文件路径
    char *first_line;                 // 首行数据
    FIL file;
    uint8_t isopen;
} LogFileHandler; // 日志管理结构

/**
 * @brief 扫描指定路径下的指定格式名称文件,并删除不符合格式或时间戳太旧的文件
 *
 * @param info
 */
void LogFile_Scan_File(LogFileHandler *info);

/**
 * @brief 扫描指定路径下的目录
 *
 */
void LogFile_Scan_Dir(void);
/**
 * @brief 清空目录
 *
 * @param info
 */
void LogFile_Clean(LogFileHandler *info);
/**
 * @brief 新建一个log文件
 *
 * @param info
 */
void LogFile_New(LogFileHandler *info);

/**
 * @brief 保持日志到文件，并检测文件大小，超过上限自动新建文件
 *
 * @param info
 * @param log
 * @param len
 * @return int
 */
int LogFile_Write(LogFileHandler *info, const char *log, int len);
#endif // PACKAGES_SD_DRIVER_SD_LOGFILE_H_
