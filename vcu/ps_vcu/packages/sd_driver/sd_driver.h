/*
 * @Author: dding3
 * @Date: 2025-03-19 15:51:57
 * @LastEditors: dding3
 * @LastEditTime: 2025-03-21 15:23:15
 * @Description:
 * @FilePath: \ps_vcu\packages\sd_driver\sd_driver.h
 */
#ifndef PACKAGES_SD_DRIVER_SD_DRIVER_H_
#define PACKAGES_SD_DRIVER_SD_DRIVER_H_

#include "main.h"
#include "fatfs.h"

typedef enum
{
    eDisk_SD = 0,
    eDisk_Num
} Disk_List_EnumDef; // 磁盘资源列表

typedef enum
{
    eStatus_Invalid = 0,
    eStatus_Valid = 1
}status_EnumDef;

int32_t Disk_Mount(void);
status_EnumDef Disk_Status_Get(Disk_List_EnumDef disk);

void Disk_Test_Write(void);
void Disk_Test_Read(void);
#endif // PACKAGES_SD_DRIVER_SD_DRIVER_H_
