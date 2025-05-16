/**
 ******************************************************************************
 * @file    flash.c
 * @brief   flash驱动模块
 * @attention None
 * Change Logs:
 * Date                     Author                  Notes
 * 2021/08/17               maxiang                 initial
 ******************************************************************************
 */
#include "flash.h"
#include "fwlib_cfg.h"
#include "elog.h"

#define PACK_LE_32(p) (*(p + 3) << 24 | *(p + 2) << 16 | *(p + 1) << 8 | *(p))

// Base address of the Flash sectors
#define FLASH_ADDR_00_SECTOR  ((uint32_t)0x08000000) // Base @ of Sector 0, 32 Kbytes
#define FLASH_ADDR_01_SECTOR  ((uint32_t)0x08020000) // Base @ of Sector 1, 32 Kbytes
#define FLASH_ADDR_02_SECTOR  ((uint32_t)0x08040000) // Base @ of Sector 2, 32 Kbytes
#define FLASH_ADDR_03_SECTOR  ((uint32_t)0x08060000) // Base @ of Sector 3, 32 Kbytes
#define FLASH_ADDR_04_SECTOR  ((uint32_t)0x08080000) // Base @ of Sector 4, 128 Kbytes
#define FLASH_ADDR_05_SECTOR  ((uint32_t)0x080a0000) // Base @ of Sector 5, 256 Kbytes
#define FLASH_ADDR_06_SECTOR  ((uint32_t)0x080c0000) // Base @ of Sector 6, 256 Kbytes
#define FLASH_ADDR_07_SECTOR  ((uint32_t)0x080e0000) // Base @ of Sector 7, 256 Kbytes

static uint16_t flash_sector_calc(uint32_t addr)
{
    uint16_t sector_num = 0;

    // 地址范围合法性检查
    if (addr < FLASH_ADDR_00_SECTOR || addr > FLASH_ADDR_07_SECTOR)
    {
        sector_num = 255;

        return sector_num;
    }

    if (addr == FLASH_ADDR_00_SECTOR)
        sector_num = FLASH_SECTOR_0;
    else if (addr == FLASH_ADDR_01_SECTOR)
        sector_num = FLASH_SECTOR_1;
    else if (addr == FLASH_ADDR_02_SECTOR)
        sector_num = FLASH_SECTOR_2;
    else if (addr == FLASH_ADDR_03_SECTOR)
        sector_num = FLASH_SECTOR_3;
    else if (addr == FLASH_ADDR_04_SECTOR)
        sector_num = FLASH_SECTOR_4;
    else if (addr == FLASH_ADDR_05_SECTOR)
        sector_num = FLASH_SECTOR_5;
    else if ((addr >= FLASH_ADDR_06_SECTOR) && (addr < FLASH_ADDR_07_SECTOR))
        sector_num = FLASH_SECTOR_6;
    else if (addr == FLASH_ADDR_07_SECTOR)
        sector_num = FLASH_SECTOR_7;
    else
        sector_num = 255;

    return sector_num;
}


uint16_t STMFLASH_GetFlashSector(uint32_t addr)
{
	if(addr<FLASH_ADDR_01_SECTOR)return FLASH_SECTOR_0;
	else if(addr<FLASH_ADDR_02_SECTOR)return FLASH_SECTOR_1;
	else if(addr<FLASH_ADDR_03_SECTOR)return FLASH_SECTOR_2;
	else if(addr<FLASH_ADDR_04_SECTOR)return FLASH_SECTOR_3;
	else if(addr<FLASH_ADDR_05_SECTOR)return FLASH_SECTOR_4;
	else if(addr<FLASH_ADDR_06_SECTOR)return FLASH_SECTOR_5;
	else if(addr<FLASH_ADDR_07_SECTOR)return FLASH_SECTOR_6;
	return FLASH_SECTOR_7;	
}
/**
 * @brief flash擦除函数
 * @param addr flash地址
 * @retval None
 */
void flash_erase(uint32_t addr)
{
    uint32_t SectorError=0;
    HAL_StatusTypeDef FlashStatus=HAL_OK;
    FLASH_EraseInitTypeDef FlashEraseInit;
    HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *SectorError);

    uint32_t sector = STMFLASH_GetFlashSector(addr);
    HAL_FLASH_Unlock();             //����
    FlashEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;       //�������ͣ��������� 
    FlashEraseInit.Banks = FLASH_BANK_1;
    FlashEraseInit.Sector = sector;   //Ҫ����������
    FlashEraseInit.NbSectors= 1 ;                             //һ��ֻ����һ������
    FlashEraseInit.VoltageRange=FLASH_VOLTAGE_RANGE_3;      //��ѹ��Χ��VCC=2.7~3.6V֮��!!
ERASE_RESET:
    if(HAL_FLASHEx_Erase(&FlashEraseInit,&SectorError)!=HAL_OK) 
    {
        printf("erase flash:%x error[%d][%d]\n",addr,FLASH_BANK_1,sector);
        goto ERASE_RESET;
    }
    //SCB_CleanInvalidateDCache();
    FlashStatus = FLASH_WaitForLastOperation(0xffff,FLASH_BANK_1);
	if(FlashStatus!=HAL_OK)
	{
        //
	} 
    HAL_FLASH_Lock();           //����
}

/**
 * @brief flash多字节读取函数
 * @param addr flash地址
 * @param data 数据缓存区指针
 * @param len 读取字节数
 */
uint8_t STMFLASH_ReadByte(uint32_t faddr)
{
	return *(__IO uint32_t *)faddr; 
}
void flash_read_bytes(uint32_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead)
{
    HAL_StatusTypeDef FlashStatus=HAL_OK;
    uint32_t endaddr;
    uint32_t word;
    endaddr=ReadAddr+NumToRead;	//д��Ľ�����ַ
    if(endaddr > 0x081FFFFF)return HAL_ERROR;
    while(ReadAddr<endaddr)//д����
    {
        *pBuffer = STMFLASH_ReadByte(ReadAddr);
        ReadAddr += 1;
        pBuffer  += 1;
    }   
    //memcpy(pBuffer, (void *)ReadAddr, NumToRead);
    
    return HAL_OK;
}

void flash_program_prepare(void)
{
#if 1
    HAL_FLASH_Unlock();

    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR | FLASH_FLAG_PGSERR_BANK1 | FLASH_FLAG_STRBERR_BANK1 | FLASH_FLAG_INCERR_BANK1
                            );
#endif
}

void flash_program(uint32_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite)
{
    HAL_StatusTypeDef FlashStatus=HAL_OK;

	uint32_t endaddr=0;	
    endaddr = WriteAddr+NumToWrite;
    if(endaddr > 0x081FFFFF)return HAL_ERROR;
    if(endaddr < 0x08000000)return HAL_ERROR;
    if(WriteAddr%4)return HAL_ERROR;

    if(((WriteAddr - 0x08000000) % 0x20000) == 0)
    {
        flash_erase(WriteAddr);
        printf("erase flash:%x success\n",WriteAddr);
    }

    // flash_program_prepare();             //����	
    HAL_FLASH_Unlock();             //����	
    FlashStatus =FLASH_WaitForLastOperation(0xffff,FLASH_BANK_1);            //�ȴ��ϴβ������
	if( FlashStatus != HAL_OK ){
        printf("flash_program status error\n");
        return FlashStatus;
	}
	for (int i = 0; i < NumToWrite / 32; i++)	
	{
        
		
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, WriteAddr, (uint64_t)pBuffer) == HAL_OK)
		{
			WriteAddr = WriteAddr + 32; /* ������������һ��256bit */
            pBuffer += 32;				
		}		
		else
		{
			goto err;
		}

        
	}
	
	/* ���Ȳ���32�ֽ������� */
	if (NumToWrite % 32)
	{
		uint64_t FlashWord[4];

        memset(FlashWord,0xff,32);
		memcpy((char *)FlashWord, pBuffer, NumToWrite % 32);
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, WriteAddr, (uint64_t)((uint32_t)FlashWord)) == HAL_OK)
		{
			; // _ulFlashAddr = _ulFlashAddr + 32;		
		}		
		else
		{
			goto err;
		}
	}  
  	/* Flash ��������ֹдFlash���ƼĴ��� */
  	HAL_FLASH_Lock();

  	__set_PRIMASK(0);  		/* ���ж� */

	return HAL_OK;
	
err:
  	/* Flash ��������ֹдFlash���ƼĴ��� */
  	HAL_FLASH_Lock();

  	__set_PRIMASK(0);  		/* ���ж� */
    return HAL_ERROR;
}

void flash_program_finish(void)
{
#if 1
    HAL_FLASH_Lock();
#endif
}


#define ADDR_FLASH_SECTOR_7_BANK1 0x8040000
#define test_length 128
uint8_t w_data[test_length];
uint8_t r_data[test_length];
int stmflash_test(){
    uint32_t SectorError=0;

    
    flash_erase( ADDR_FLASH_SECTOR_7_BANK1 );
    memset(r_data,0x00,test_length);
    flash_read_bytes( ADDR_FLASH_SECTOR_7_BANK1,r_data,test_length);
    printf("read1:");
    for( uint16_t i = 0; i < 20; i++ ){
        printf("%02X ", r_data[i]);
    }
    printf("\r\n");
    
    for(uint16_t i = 0; i < test_length; i++ )
    {
        w_data[i] = i;
    }
    printf("write:");
    for( uint16_t i = 0; i < test_length; i++ ){
        printf("%02X ", w_data[i]);
    }
    printf("\r\n");
    HAL_Delay(1000);
    flash_program( ADDR_FLASH_SECTOR_7_BANK1,w_data,test_length);
    
    
    flash_read_bytes( ADDR_FLASH_SECTOR_7_BANK1,r_data,test_length);
    printf("read2:");
    for( uint16_t i = 0; i < test_length; i++ ){
        printf("%02X ", r_data[i]);
    }
    printf("\r\n");    
    HAL_Delay(1000);
    
    return 1;
}