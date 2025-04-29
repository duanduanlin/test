/*
 * @Author: dding3
 * @Date: 2025-03-27 09:44:37
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-27 18:13:55
 * @Description:
 * @FilePath: \ps_vcu\packages\sd_driver\sd_driver.c
 */

#include "stdio.h"
#include "string.h"
#include "fatfs.h"
#include "sd_driver.h"
#include "sdmmc.h"

static int32_t Disk_Mount_SD(void);

static status_EnumDef disk_state[eDisk_Num] = {eStatus_Invalid}; // 磁盘状态

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

/****************************************
@function:磁盘挂载
@param:void
@return:-1--失败,0--正常
@note:
****************************************/
int32_t Disk_Mount(void)
{
    if (Disk_Mount_SD() < 0)
    {
        disk_state[eDisk_SD] = eStatus_Invalid;
        return -1;
    }
    else
    {
        disk_state[eDisk_SD] = eStatus_Valid;
    }

    // Disk_File_Read_SystemParameter();
    return 0;
}

/****************************************
@function:挂载磁盘-SD卡
@param:void
@return:-1--失败,0--正常
@note:
****************************************/
static int32_t Disk_Mount_SD(void)
{
    //    BYTE work[_MAX_SS];
    HAL_SD_CardInfoTypeDef SdCard;

    // retSD = f_mount(&SDFatFS, SDPath, 1); // 挂载盘符A
    // if (retSD == FR_NO_FILESYSTEM)        // 没有文件系统就格式化创建创建文件系统
    // {
    //     printf("no filesystem\n");
    //     // retSD = f_mkfs(SDPath, FS_FAT32, 0, work, sizeof(work));
    //     // if (retSD == FR_OK)
    //     // {
    //     //     retSD = f_mount(NULL, SDPath, 1);     // 格式化后，先取消挂载
    //     //     retSD = f_mount(&SDFatFS, SDPath, 1); // 挂载
    //     // }
    //     // else // 格式化失败
    //     // {
    //     //     printf("Description Failed to format the SD card...%d\n", retSD);
    //     //     goto SD_FAIL;
    //     // }
    // }
    // else if (retSD != FR_OK) // 挂载失败
    // {
    //     printf("Mount failure=%d\n", retSD);
    //     goto SD_FAIL;
    // }

    retSD = f_mount(&SDFatFS, SDPath, 1);
    if (retSD != FR_OK)
    {
        printf("f_mount():retSD=%d\n", retSD);
        goto SD_FAIL;
    }

    if (HAL_SD_GetCardInfo(&hsd1, &SdCard) != HAL_OK)
    {
        printf("HAL_SD_GetCardInfo()\n");
        goto SD_FAIL;
    }
    printf("SD valume:%.2fGB\n", (float)((uint64_t)SdCard.BlockNbr * (uint64_t)SdCard.BlockSize / 1024.0f / 1024.0f / 1024.0f));

    return 0;
SD_FAIL:
{
    printf("Error[Disk_Mount_SD()]:The disk fails to be mounted...\n");
    return -1;
}
}

/****************************************
@function:获取磁盘状态
@param:void
@return:见status_EnumDef
@note:
****************************************/
status_EnumDef Disk_Status_Get(Disk_List_EnumDef disk)
{
    return disk_state[disk];
}

void Disk_Test_Write(void)
{
    BYTE WriteBuffer[] = "Hello World!\n";
    UINT fnum = 0;
    retSD = f_open(&SDFile, "log/vcu-21.log", FA_CREATE_ALWAYS | FA_WRITE);
    if (retSD == FR_OK)
    {
        printf("file open success\r\n");
        /* 将指定存储区内容写入到文件内 */
        retSD = f_write(&SDFile, WriteBuffer, sizeof(WriteBuffer), &fnum);
        if (retSD == FR_OK)
        {
            printf("file write success:%d\n", fnum);
            printf("data write:\r\n%s\r\n", WriteBuffer);
        }
        else
        {
            printf("file write failed (%d)\n", retSD);
        }
        /* 不再读写，关闭文件 */
        f_close(&SDFile);
    }
    else
    {
        printf("file open failed\r\n");
    }
}

void Disk_Test_Read(void)
{
    BYTE ReadBuffer[128] = {0};
    UINT fnum = 0;
    retSD = f_open(&SDFile, "test.txt", FA_OPEN_EXISTING | FA_READ);
    if (retSD == FR_OK)
    {
        printf("file open success\r\n");
        retSD = f_read(&SDFile, ReadBuffer, sizeof(ReadBuffer), &fnum);
        if (retSD == FR_OK)
        {
            printf("file read success:%d\r\n", fnum);
            printf("data read:\r\n%s \r\n", ReadBuffer);
        }
        else
        {
            printf("file read failed (%d)\n", retSD);
        }
    }
    else
    {
        printf("file open failed\r\n");
    }
    /* 不再读写，关闭文件 */
    f_close(&SDFile);
}

void Disk_Show_Info(void)
{
    DWORD nclst;
    if (f_getfree("", &nclst, &SDFatFS) == FR_OK)
    {
        printf("free %u\r\n", nclst);
    }
}
