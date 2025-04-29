#ifndef OTA_APP_H
#define OTA_APP_H


#include "stdint.h"


#define APP_VERSION             "1.1.0"

#define OTA_PARAM_FLASH_SEC     FLASH_SECTOR_1
#define OTA_PARAM_FLASH_ADDR    0x08020000

#define BOARD_MODULE_ADDR       MODULE_VCU


typedef struct __attribute__((packed)){
	uint8_t Board_ID_Sour;	//板卡序号
	uint8_t Board_ID_Dest;	//板卡序号
	uint8_t status;
	uint8_t unused[4];
	uint8_t OTA_200_CheckSum;
}OTA_200_ALLOW_REC;

/*重启完成状态*/
typedef struct __attribute__((packed)){
	uint8_t Board_ID_Sour;//板卡序号
	uint8_t Board_ID_Dest;//板卡序号
	uint8_t status;		    //状态

	uint8_t unused[4];
	uint8_t OTA_206_CheckSum;

}OTA_206_RebootFinish_Status;

typedef struct __attribute__((packed)){
	uint8_t Board_ID_Sour;//板卡序号
	uint8_t Board_ID_Dest;//板卡序号
	uint8_t check;		    //检查标志 置1开始发送app版本  0发送boot版本

	uint8_t unused[4];
	uint8_t OTA_209_CheckSum;

}OTA_209_Query_ver;

typedef struct __attribute__((packed))
{
    uint8_t Board_ID_Sour;//板卡序号
	uint8_t Board_ID_Dest;//板卡序号

    uint8_t status;//0:打开升级转发 1:关闭升级转发

    uint8_t unused[4];
    uint8_t checksum;
}OTA_211_CMD_t;



/*运控版本*/
typedef struct __attribute__((packed)){
		uint8_t Board_ID_Sour;//板卡序号
		uint8_t Board_ID_Dest;//板卡序号
        uint8_t run_area : 4;       // 低4位（第3字节的低4位） 运行区域
        uint8_t version_type : 4;    // 高4位（第3字节的高4位）反馈的版本类型 0：boot版本 1：app版本
		uint8_t update_status;     //升级标志

		uint8_t version1; 		//大版本
		uint8_t version2;     //子版本
		uint8_t version3;			//小版本
		uint8_t OTA_210_CheckSum;
}OTA_210_ver;



enum
{
    OTA_CMD_200 = 0x200,  //to app, firmware update notify
    OTA_CMD_201,        //?, upgrade authentication
    OTA_CMD_202_START,  //to upupgrade permit
    OTA_CMD_203_DATA,   //upgrade data transfer
    OTA_CMD_204_ACK,    //upgrade data transfer respond
    OTA_CMD_205_REBOOT, //reboot
    OTA_CMD_206,        //upgrade complete
    OTA_CMD_209 = 0x209,  //check version
    OTA_CMD_210,        //response version
    OTA_CMD_211,
};

//板卡地址
enum
{
    MODULE_Tbox = 0,
    MODULE_ADCU,
    MODULE_RDCU,
    MODULE_VCU,
    MODULE_PMU,
    MODULE_CCU,
    MODULE_MCU_L,
    MODULE_MCU_R,
    MODULE_EPS ,
    MODULE_OBD,
    MODULE_ECU_TG1000_1 ,
    MODULE_ECU_TG1000_2,
    MODULE_ECU_TG1000_3,
    MODULE_ECU_TG1000_4,
    MODULE_ECU_TG1000_5,
};

//运行区域
enum
{
    RUN_AREA_BOOT = 0,
    RUN_AREA_APP,
    RUN_AREA_APP_BACKUPS,
};

//版本类型
enum
{
    VERSION_TYPE_BOOT = 0,
    VERSION_TYPE_APP,
};

//升级转发类型
enum
{
    Update_Status_Upgrading = 0,
    Update_Status_Normol,
};

#define FW_UPGRADE_NORMAL 0x00
#define FW_UPGRADE_START 0x01
#define FW_UPGRADING 0x02
#define FW_UPGRADE_END 0x03
#define FW_UPGRADE_WRITTEN 0x04
#define FW_UPGRADE_IN_BOOT 0x05
#define FW_UPGRADE_MAX 0x06


#define MAX_VERSION_STR 10

typedef struct __attribute__((packed))
{
    uint16_t upgrade_flag;
    uint16_t running_safe_flag; //
    uint8_t bootloader_version[MAX_VERSION_STR];
    uint8_t app_version[MAX_VERSION_STR];
    uint32_t load_firmware_size; //0, 为了与boot对齐
    uint16_t checksum; // crc16校验码
    uint16_t UNUSED; // 4字节对齐
} upgrade_param_type;



uint8_t is_upd(void);
void power_up_ota_handle(void);
void msg_packet_209_handler(uint8_t *buf);
void msg_packet_200_handler(uint8_t *buf);
void msg_packet_211_handler(uint8_t *buf);

#endif // !OTA_APP_H
