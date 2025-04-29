/*
 * @Author: dding3
 * @Date: 2025-03-27 10:44:24
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-27 16:28:36
 * @Description:
 * @FilePath: \ps_vcu\packages\sd_driver\sd_logfile.c
 */
#include "rtc.h"
#include "sd_logfile.h"
#include "stdio.h"
#include "string.h"

/**
 * @brief 删除文件
 *
 * @param path
 */
static void delete_file(const char *path)
{
    if (f_unlink(path) != FR_OK)
    {
        printf("file %s delete failed\r\n", path);
    }
}

/**
 * @brief 递归清理文件夹
 *
 * @param path
 */
static void clean_dir(const char *path)
{
    FRESULT fr;
    DIR dir;
    FILINFO fno;                // 文件信息结构体
    fr = f_opendir(&dir, path); // 打开文件目录
    if (fr == FR_OK)
    {
        for (;;)
        {                               // 循环读出文件名字，循环次数等于SD卡根目录下的文件数目
            fr = f_readdir(&dir, &fno); // 读取文件名
            if (fr != FR_OK || fno.fname[0] == 0)
                break; // 读取错误或者读完所有文件结束就跳出循环
            TCHAR file[FILE_NAME_LEN_MAX] = {0};
            snprintf((char *)file, FILE_NAME_LEN_MAX, "%s/%s", path, fno.fname);
            if (fno.fattrib & AM_DIR) // 读取的是文件夹
            {
                clean_dir(file); // 递归删除
            }
            else
            {
                delete_file(file);
            }
        }
        f_closedir(&dir); // 关闭文件目录
        delete_file(path);
    }
}

void LogFile_Scan_File(LogFileHandler *info)
{
    FRESULT fr;
    DIR dir;
    FILINFO fno; // 文件信息结构体
    printf("scan file at /%s\r\n", info->path);
    fr = f_opendir(&dir, info->path); // 打开文件目录

    if (fr == FR_OK)
    {
        for (;;)
        {                               // 循环读出文件名字，循环次数等于SD卡根目录下的文件数目
            fr = f_readdir(&dir, &fno); // 读取文件名
            if (fr != FR_OK || fno.fname[0] == 0)
                break; // 读取错误或者读完所有文件结束就跳出循环
            if (fno.fattrib & AM_DIR)
            {
                printf("unexcept dir %s\t%d, will delete\r\n", fno.fname, fno.fsize);
                delete_file(fno.fname);
            }
            else
            {
                printf("file %s\t%d\r\n", fno.fname, fno.fsize);
                long timestamps = 0;
                int need_delete = 0;
                // int ret = sscanf(fno.fname, "vcu-%d-%u.log", &ser, &timestamps);
                // printf("ret %d,ser %d,timestamps %d\r\n", ret, ser, timestamps);
                if (sscanf(fno.fname, info->name_pattern, &timestamps) != 1)
                {
                    need_delete = 1;
                    printf("unknown file %s\t%d will delete\r\n", fno.fname, fno.fsize);
                }
                else
                {
                    if (info->timestamps_last < timestamps)
                    {
                        info->timestamps_last = timestamps;
                    }

                    if (info->timestamps_last - timestamps > LOG_FILE_SAVE_TIME)
                    {
                        need_delete = 1;
                        printf("over time file %s\t%d will delete\r\n", fno.fname, fno.fsize);
                    }
                }

                if (need_delete)
                {
                    TCHAR file[FILE_NAME_LEN_MAX] = {0};
                    snprintf((char *)file, FILE_NAME_LEN_MAX, "%s/%s", info->path, fno.fname);
                    delete_file(file);
                }
            }
        }
        printf("scan file at /%s done\r\n", info->path);
        printf("timestamps_last %d\r\n", info->timestamps_last);
        f_closedir(&dir); // 关闭文件目录
    }
    else
    {
        printf("%s dir is not exist,will create\r\n", info->path);
        if (f_mkdir(info->path) != FR_OK)
        {
            printf("%s dir create failed\r\n", info->path);
        }
    }
}

void LogFile_Scan_Dir(void)
{
    FRESULT fr;
    DIR dir;
    FILINFO fno;              // 文件信息结构体
    fr = f_opendir(&dir, ""); // 打开文件目录
    printf("scan dir at /%s\r\n", "");
    if (fr == FR_OK)
    { // 如果打开成功循环读出文件名字到buff中
        for (;;)
        {                               // 循环读出文件名字，循环次数等于SD卡根目录下的文件数目
            fr = f_readdir(&dir, &fno); // 读取文件名
            if (fr != FR_OK || fno.fname[0] == 0)
                break;                // 读取错误或者读完所有文件结束就跳出循环
            if (fno.fattrib & AM_DIR) // 读取的是文件夹名字
            {
                if (fno.fattrib & AM_HID)
                {
                    printf("hid dir %s\t%d \r\n", fno.fname, fno.fsize);
                }
                else
                {
                    printf("dir %s\t%d \r\n", fno.fname, fno.fsize);
                    if (strcmp(fno.fname, "log") != 0 && strcmp(fno.fname, "data") != 0)
                    {
                        printf("unexcept dir %s\t%d, will delete\r\n", fno.fname, fno.fsize);
                        // clean_dir(fno.fname);
                        delete_file(fno.fname);
                    }
                }
            }
            else
            {
                printf("unexcept file %s\t%d, will delete\r\n", fno.fname, fno.fsize);
                delete_file(fno.fname);
            }
        }
        f_closedir(&dir); // 关闭文件目录
    }
    printf("scan /%s done\r\n", "");
}

void LogFile_Clean(LogFileHandler *info)
{
    printf("dir %s will clean\r\n", info->path);
    clean_dir(info->path);
}

void LogFile_Clean_ByTimestamps(LogFileHandler *info, long timestamps)
{
}

void LogFile_New(LogFileHandler *info)
{
    snprintf(info->name, FILE_NAME_LEN_MAX, info->name_pattern, RTC_GetTimestamps());
    // check
    if (info->isopen)
    {
        printf("%s file is not close,will close\r\n", info->name);
        f_close(&info->file);
        info->isopen = 0;
    }

    snprintf(info->filePath, FILE_NAME_LEN_MAX, "%s/%s", info->path, info->name);
    printf("open new log, path: %s\r\n", info->filePath);

    if (f_open(&info->file, info->filePath, FA_CREATE_ALWAYS | FA_WRITE) != FR_OK)
    {
        printf("file %s open failed\r\n", info->filePath);
    }
    else
    {
        if (info->first_line != NULL)
        {
            UINT fnum = 0;
            if (f_write(&info->file, info->first_line, strlen(info->first_line), &fnum) != FR_OK)
            {
                printf("file %s write failed\r\n", info->filePath);
            }
            f_sync(&info->file);
        }
        info->isopen = 1;
    }
}

int LogFile_Write(LogFileHandler *info, const char *log, int len)
{
    FILINFO fno;
    UINT fnum = 0;

    if (info->isopen)
    {
        if (f_stat(info->filePath, &fno) == FR_OK)
        {
            // printf("file size %d\r\n", fno.fsize);
            if (fno.fsize > LOG_FILE_MAX_SIZE)
            {
                printf("file %s is too large:%d,will create new\r\n", info->filePath, fno.fsize);
                LogFile_New(info);
            }
        }

        if (f_write(&info->file, log, len, &fnum) != FR_OK)
        {
            printf("log write failed\r\n");
            // HAL_Delay(100);
        }
        else
        {
            f_sync(&info->file);
        }
    }

    return fnum;
}
