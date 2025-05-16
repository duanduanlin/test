#ifndef __PARAM_H__
#define __PARAM_H__

#include <stdint.h>

#define MAX_VERSION_STR 10

typedef struct __attribute__((packed))
{
    uint16_t upgrade_flag;
    uint16_t running_safe_flag;
    uint8_t bootloader_version[MAX_VERSION_STR];
    uint8_t app_version[MAX_VERSION_STR];
    uint32_t load_firmware_size;
    uint16_t checksum; // crc16校验码
} upgrade_param_type;

extern upgrade_param_type upgrade_param;

void boot_param_handler(void);
void boot_param_write(void);

#endif /* __PARAM_H__ */
