#include "modules/ota_app.h"
#include "main.h"
#include "modules/crc16.h"
#include "modules/data_handle.h"
#include "string.h"
#include "stdio.h"

static upgrade_param_type upgrade_param;
static uint8_t update_transmit_status=0;


int can_send_msg(uint32_t id, const uint8_t *data, uint8_t len)
{
    CanMsg msg = {0};
    msg.id = id;
    msg.len = len;
    memcpy(&msg.buffer, data, len);

	return Data_Handle_Write(CanNetA, &msg);
}

//*data:获取的flash内部升级参数
static void Read_Flash_Upgrade_Param(const upgrade_param_type *data)
{
    uint8_t *r_buf;

    r_buf = (uint8_t *)data;

    for(uint8_t i=0; i < sizeof(upgrade_param_type); i++)
    {
        r_buf[i] = *(volatile uint8_t *)(OTA_PARAM_FLASH_ADDR + i);
    }
}

static void Write_Flash_Upgrade_Param(upgrade_param_type *data)
{
    uint32_t SectorError;
    uint32_t *w_buf;
    FLASH_EraseInitTypeDef Flash_erase;
    HAL_StatusTypeDef FlashStatus=HAL_OK;

    HAL_FLASH_Unlock();               //解锁Flash
    Flash_erase.Banks = FLASH_BANK_1;
    Flash_erase.VoltageRange = FLASH_VOLTAGE_RANGE_3;
    Flash_erase.NbSectors = 1;
    Flash_erase.Sector = OTA_PARAM_FLASH_SEC;
    Flash_erase.TypeErase = FLASH_TYPEERASE_SECTORS;

    HAL_FLASHEx_Erase(&Flash_erase, &SectorError);
    FlashStatus = FLASH_WaitForLastOperation(0xffff,FLASH_BANK_1);
	if(FlashStatus!=HAL_OK)
	{
	}

    w_buf = &upgrade_param;

    HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, OTA_PARAM_FLASH_ADDR , data); //write 256bit == 32byte

    FlashStatus = FLASH_WaitForLastOperation(0xffff,FLASH_BANK_1);
    HAL_FLASH_Lock();
}

/*
*buf: can数据内容
*/
void msg_packet_209_handler(uint8_t *buf)
{
    printf("callback 209\r\n");

    OTA_209_Query_ver version_rec_content;
    OTA_210_ver version_check_ack_content;
    uint8_t version_buf[3];

    memcpy(&version_rec_content, buf, sizeof(version_rec_content));

    if(version_rec_content.Board_ID_Dest != BOARD_MODULE_ADDR) return;


    Read_Flash_Upgrade_Param(&upgrade_param);
    version_check_ack_content.Board_ID_Sour = BOARD_MODULE_ADDR;
    version_check_ack_content.Board_ID_Dest = MODULE_ADCU;
    version_check_ack_content.run_area = RUN_AREA_APP;
    version_check_ack_content.update_status = upgrade_param.upgrade_flag;

    if(version_rec_content.check == VERSION_TYPE_BOOT)
    {
        version_check_ack_content.version_type = VERSION_TYPE_BOOT;

        char *token;
        char temp_str[16] = {0};
        memcpy(temp_str, upgrade_param.bootloader_version, sizeof(upgrade_param.bootloader_version));

        token = strtok(temp_str, ".");
        version_buf[0] = atoi(token);

        token = strtok(NULL, ".");
        version_buf[1] = atoi(token);

        token = strtok(NULL, ".");
        version_buf[2] = atoi(token);
        // sscanf((void *)upgrade_param.bootloader_version, "%d.%d.%d", &version_buf[0], &version_buf[1], &version_buf[2]);
        version_check_ack_content.version1 = version_buf[0];
        version_check_ack_content.version2 = version_buf[1];
        version_check_ack_content.version3 = version_buf[2];
    }
    else if(version_rec_content.check == VERSION_TYPE_APP)
    {
        version_check_ack_content.version_type = VERSION_TYPE_APP;

        char *token;
        char temp_str[16] = {0};
        memcpy(temp_str, upgrade_param.app_version, sizeof(upgrade_param.app_version));

        token = strtok(temp_str, ".");
        version_buf[0] = atoi(token);

        token = strtok(NULL, ".");
        version_buf[1] = atoi(token);

        token = strtok(NULL, ".");
        version_buf[2] = atoi(token);

        version_check_ack_content.version1 = version_buf[0];
        version_check_ack_content.version2 = version_buf[1];
        version_check_ack_content.version3 = version_buf[2];
    }

    version_check_ack_content.OTA_210_CheckSum = calc_checksum(&version_check_ack_content, sizeof(version_check_ack_content)-1);
    //直接发送，不做数据缓冲
    can_send_msg(OTA_CMD_210, (uint8_t *)&version_check_ack_content, sizeof(version_check_ack_content));
}


void msg_packet_200_handler(uint8_t *buf)
{
    OTA_200_ALLOW_REC rec_content;
    OTA_200_ALLOW_REC pack_content;
    uint8_t checksum=0;

    printf("callback 200\r\n");

    memcpy(&rec_content, buf, sizeof(OTA_200_ALLOW_REC));

    if(rec_content.Board_ID_Dest != BOARD_MODULE_ADDR) return;


    Read_Flash_Upgrade_Param(&upgrade_param);


    pack_content.Board_ID_Sour = BOARD_MODULE_ADDR;
    pack_content.Board_ID_Dest = MODULE_ADCU;
    pack_content.status = 1;
    for(uint8_t i=0;i<4;i++)pack_content.unused[i] = 0x00;
    pack_content.OTA_200_CheckSum = calc_checksum(&pack_content,sizeof(OTA_200_ALLOW_REC)-1);

    upgrade_param.load_firmware_size = 0x00;
    upgrade_param.upgrade_flag = FW_UPGRADE_START;

    upgrade_param.checksum = calc_crc16_table((uint8_t *)&upgrade_param, sizeof(upgrade_param) - 2);

    Write_Flash_Upgrade_Param(&upgrade_param);

    //直接发送，不做数据缓冲
    can_send_msg(OTA_CMD_200,&pack_content,sizeof(OTA_200_ALLOW_REC));
    printf("will goto boot\r\n");

    osDelay(500);
    //复位重启
    HAL_NVIC_SystemReset();
}



void msg_packet_211_handler(uint8_t *buf)
{
    OTA_211_CMD_t rec_content;
    OTA_211_CMD_t pack_content;

    printf("callback 211\r\n");

    memcpy(&rec_content, buf, sizeof(OTA_200_ALLOW_REC));

    if(rec_content.Board_ID_Dest != BOARD_MODULE_ADDR) return;

    if(rec_content.status == Update_Status_Upgrading)
    {
        update_transmit_status = 1;
    }
    else
    {
        update_transmit_status = 0;
    }

    pack_content.Board_ID_Sour = BOARD_MODULE_ADDR;
    pack_content.Board_ID_Dest = MODULE_ADCU;
    pack_content.status = 0;
    for(uint8_t i=0;i<4;i++)pack_content.unused[i] = 0x00;
    pack_content.checksum = calc_checksum(&pack_content, sizeof(pack_content)-1);
    //直接发送，不做数据缓冲
    can_send_msg(OTA_CMD_211,&pack_content,sizeof(OTA_211_CMD_t));
}


//return: 0:正常模式 1:升级转发中
uint8_t is_upd(void)
{
    return update_transmit_status;
}


void power_up_ota_handle(void)
{
    uint8_t *buf;
    OTA_206_RebootFinish_Status ack_content;

    //板卡ID判断,待实现

    Read_Flash_Upgrade_Param(&upgrade_param);

    strncpy((void *)&upgrade_param.app_version, APP_VERSION, sizeof(upgrade_param.app_version));

    upgrade_param.running_safe_flag = 0;

    if(upgrade_param.upgrade_flag == FW_UPGRADE_END)
    {
        ack_content.Board_ID_Sour = BOARD_MODULE_ADDR;
        ack_content.Board_ID_Dest = MODULE_ADCU;
        ack_content.status = 1;

        upgrade_param.upgrade_flag = FW_UPGRADE_NORMAL;

        buf = &ack_content;
        for(uint8_t i=0;i<7;i++)
        {
            ack_content.OTA_206_CheckSum += buf[i];
        }

        can_send_msg(OTA_CMD_206,&ack_content,sizeof(OTA_206_RebootFinish_Status));
    }

    upgrade_param.checksum = calc_crc16_table((uint8_t *)&upgrade_param, sizeof(upgrade_param) - 2);

    Write_Flash_Upgrade_Param(&upgrade_param);
}
