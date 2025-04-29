/*
 * @Author: dding3
 * @Date: 2025-04-28 13:43:07
 * @LastEditors: dding3
 * @LastEditTime: 2025-04-28 16:45:09
 * @Description:
 * @FilePath: \ps_vcu\common\vcu_info.c
 */
#include "stdio.h"
#include "common/vcu_info.h"
#include "main.h"

#define VCU_INFO_FLASH_SEC     FLASH_SECTOR_0
#define VCU_INFO_FLASH_ADDR    0x08100000

typedef struct vcu_info
{
    uint32_t total_oeometer;//总里程信息
}VcuInfo;

static VcuInfo s_vcu_info;
static int s_need_save;

int Vcu_Info_Read(void)
{
    uint8_t *r_buf;

    r_buf = (uint8_t *)&s_vcu_info;

    for(uint8_t i=0; i < sizeof(VcuInfo); i++)
    {
        r_buf[i] = *(volatile uint8_t *)(VCU_INFO_FLASH_ADDR + i);
    }

    return 0;
}

int Vcu_Info_Write(void)
{
    uint32_t SectorError;
    uint32_t *w_buf;
    FLASH_EraseInitTypeDef Flash_erase;
    HAL_StatusTypeDef FlashStatus=HAL_OK;

    if(s_need_save == 0)
    {
        return -1;
    }


    HAL_FLASH_Unlock();               //解锁Flash
    Flash_erase.Banks = FLASH_BANK_2;
    Flash_erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    Flash_erase.NbSectors = 1;
    Flash_erase.Sector = VCU_INFO_FLASH_SEC;
    Flash_erase.TypeErase = FLASH_TYPEERASE_SECTORS;

    HAL_FLASHEx_Erase(&Flash_erase, &SectorError);
    FlashStatus = FLASH_WaitForLastOperation(0xffff,FLASH_BANK_2);
	if(FlashStatus!=HAL_OK)
	{
	}

    w_buf = &s_vcu_info;

    HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, VCU_INFO_FLASH_ADDR , w_buf); //write 256bit == 32byte

    FlashStatus = FLASH_WaitForLastOperation(0xffff,FLASH_BANK_2);
    HAL_FLASH_Lock();

    s_need_save = 0;
    return 0;
}

double Vcu_Info_GetOdometer(void)
{
    return s_vcu_info.total_oeometer / 1000.0f;
}

void Vcu_Info_AddOdometer(double odometer)
{
    if(odometer != 0)
    {
        s_need_save = 1;
        s_vcu_info.total_oeometer += (uint32_t)(odometer *1000);
        printf("add odometer %f,total_oeometer %d \n",odometer,s_vcu_info.total_oeometer);
    }
}
