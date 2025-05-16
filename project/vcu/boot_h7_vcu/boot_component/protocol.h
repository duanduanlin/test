#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <stdint.h>

// 升级固件块大小
#define UPGRADE_FW_BLOCK_SIZE 256
// 版本字符大小
#define UPGRADE_VERSION_CHAR_SIZE 10

//global communicating module definition
enum
{
    MODULE_DEBUG_BOARD = 1, //10-10 belongs to normal moduls
    MODULE_CONTROL_PC,
    MODULE_MOVE_CONTROL_BOARD,
    MODULE_POWER_INTEGRATE_BOARD,
    MODULE_SWEEPING_BOX_BOARD,

    MODULE_MOTOR_DRIVER_START = 10, //10-29 belongs to motor drivers
    MODULE_MOTOR_DRIVER_FRONT_LEFT = MODULE_MOTOR_DRIVER_START,
    MODULE_MOTOR_DRIVER_FRONT_RIGHT,
    MODULE_MOTOR_DRIVER_BACK_LEFT,
    MODULE_MOTOR_DRIVER_BACK_RIGHT,
    MODULE_MOTOR_TURN_FRONT,
    MODULE_MOTOR_TURN_BACK,
    MODULE_MOTOR_BRAKE_FRONT,
    MODULE_MOTOR_BREAK_BACK,
    MODULE_MOTOR_DRIVER_END = MODULE_MOTOR_BREAK_BACK,

    MODULE_LIGHT_START = 30, //30-49 belongs to lights
    MODULE_LIGHT_FRONT_LEFT = MODULE_LIGHT_START,
    MODULE_LIGHT_FRONT_RIGHT,
    MODULE_LIGHT_BACK_LEFT,
    MODULE_LIGHT_BACK_RIGHT,
    MODULE_LIGHT_BACK,
    MODULE_LIGHT_HEAD,
    MODULE_LIGHT_TAPE = 39,  //灯带板
    // MODULE_LIGHT_END = MODULE_LIGHT_HEAD,
    MODULE_LIGHT_END = MODULE_LIGHT_TAPE,

    MODULE_ULTRASONIC_START = 50,
    MODULE_ULTRASONIC_MASTER = MODULE_ULTRASONIC_START,
    MODULE_ULTRASONIC_1,
    MODULE_ULTRASONIC_2,
    MODULE_ULTRASONIC_3,
    MODULE_ULTRASONIC_4,
    MODULE_ULTRASONIC_5,
    MODULE_ULTRASONIC_6,
    MODULE_ULTRASONIC_7,
    MODULE_ULTRASONIC_8,
    MODULE_ULTRASONIC_9,
    MODULE_ULTRASONIC_10,
    MODULE_ULTRASONIC_11,
    MODULE_ULTRASONIC_12,
    MODULE_ULTRASONIC_13,
    MODULE_ULTRASONIC_14,
    MODULE_ULTRASONIC_15,
    MODULE_ULTRASONIC_16,
    MODULE_ULTRASONIC_END,
    MODULE_ULTRASONIC_RESERVED_END = 79,

    MODULE_BELOW_START = 80, //other modules start

    MAX_MODULE,
};

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

enum
{
    RUN_AREA_BOOT = 0,
    RUN_AREA_APP,
    RUN_AREA_APP_BACKUPS,
};

enum
{
    VERSION_TYPE_BOOT = 0,
    VERSION_TYPE_APP,
};

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

typedef struct __attribute__((packed))
{
    uint8_t src;
    uint8_t dest;
} update_info_type;

// [SCP_CMD_200_UPGRADE_NOTHFY]
typedef struct __attribute__((packed))
{
    update_info_type upd_info;
    uint8_t status;
    uint8_t version[10];
    uint32_t firmware_size;
    uint8_t key[64];
} upgrade_notify_content_type;

// [SCP_CMD_201_UPGRADE_VERIFY]
typedef struct __attribute__((packed))
{
    update_info_type upd_info;
    uint8_t status;
} upgrade_verify_type;

// [SCP_CMD_202_UPGRADE_PERMIT]
typedef struct __attribute__((packed))
{
    update_info_type upd_info;
    uint8_t status;
} upgrade_permit_type;

// [SCP_CMD_203_UPGRADE_FW_BLOCK]
typedef struct __attribute__((packed))
{
    update_info_type upd_info;
    uint8_t status;
    uint16_t total_packets;
    uint16_t current_packet;
    uint16_t packet_length;
    uint16_t actual_length;
    uint8_t data[UPGRADE_FW_BLOCK_SIZE]; //128, 256, 512 ,1024 且不得大于写入扇区字节大小FLASH_SECTOR_BYTE_SIZE
} upgrade_fw_block_type;

// [SCP_CMD_204_UPGRADE_FW_BLOCK_ACK]
typedef struct __attribute__((packed))
{
    update_info_type upd_info;
    uint8_t status;
    uint16_t current_packet;
} upgrade_fw_block_ack_type;

// [SCP_CMD_205_REBOOT]
typedef struct __attribute__((packed))
{
    update_info_type upd_info;
    uint8_t status;
} reboot_type;

// [SCP_CMD_206_UPGRADE_END]
typedef struct __attribute__((packed))
{
    update_info_type upd_info;
    uint8_t status;
} upgrade_end_type;

// [SCP_CMD_209_VERSION_CHECK]
typedef struct __attribute__((packed))
{
    update_info_type upd_info;
    uint8_t check;
} version_check_type;

// [SCP_CMD_210_VERSION_CHECK_ACK]
typedef struct __attribute__((packed))
{
    update_info_type upd_info;
    unsigned char run_area;
    unsigned char update_status;
    unsigned char boot_ver[UPGRADE_VERSION_CHAR_SIZE];
    unsigned char app_ver[UPGRADE_VERSION_CHAR_SIZE];
    unsigned char update_lib_ver[UPGRADE_VERSION_CHAR_SIZE];
} version_check_ack_type;

// [SCP_CMD_211_UPGRADE_STATUS]
typedef struct __attribute__((packed))
{
    update_info_type upd_info;
    unsigned char status;
    unsigned char detail; //reserved
} upgrade_status_type;

typedef struct __attribute__((packed))
{
    uint16_t upgrade_flag;
    uint16_t running_safe_flag;
    uint8_t bootloader_version[10];
    uint8_t app_version[10];
    uint32_t dload_firmware_size;
} upgrade_configuration_type;



typedef struct __attribute__((packed)){
	uint8_t Board_ID_Sour;	//板卡序号
	uint8_t Board_ID_Dest;	//板卡序号
	uint8_t status;
	uint8_t unused[4];
	uint8_t OTA_200_CheckSum;
}OTA_200_ALLOW_REC;

typedef struct __attribute__((packed)){
	uint8_t Board_ID_Sour;//板卡序号
	uint8_t Board_ID_Dest;//板卡序号
	uint8_t status;				//当前状态
	uint8_t unused[4];
	uint8_t OTA_202_CheckSum;
	
}OTA_202_NowStatus;

#pragma pack(push, 1)  // 1字节对齐
typedef struct __attribute__((packed)){
	uint8_t Board_ID_Sour;//板卡序号
	uint8_t Board_ID_Dest;//板卡序号
	uint8_t packs;				//数据包序号
	uint8_t data_N[4];
	uint8_t OTA_203_CheckSum;
	
}OTA_203_cir_send;
#pragma pack(pop)      // 恢复默认对齐

/*回复收到文件的状态*/
typedef struct __attribute__((packed)){
	uint8_t Board_ID_Sour;//板卡序号
	uint8_t Board_ID_Dest;//板卡序号
	uint8_t status;		    //状态:0 :有误       1:正确
	uint8_t packs;				//数据包序号
	uint8_t unused[3];//current_packet
	uint8_t OTA_204_CheckSum;
	
}OTA_204_RecStatus;

/*重启状态*/
typedef struct __attribute__((packed)){

	uint8_t Board_ID_Sour;//板卡序号
	uint8_t Board_ID_Dest;//板卡序号
	uint8_t status;		    //状态 1 重启

	uint8_t unused[4];
	uint8_t OTA_205_CheckSum;
	
}OTA_205_RebootStatus;


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

/*回复可以升级 */
typedef struct __attribute__((packed)){
	uint8_t Board_ID_Sour;//板卡序号
	uint8_t Board_ID_Dest;//板卡序号
	uint8_t Status;		    //1 可以升级

	uint8_t unused[4];
	uint8_t OTA_211_CheckSum;
	
}OTA_211_ALLOW_up;
#endif /* __PROTOCOL_H__ */
