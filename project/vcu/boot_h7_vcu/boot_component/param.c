#include "param.h"
#include "app.h"

upgrade_param_type upgrade_param;

static void report_param_info(upgrade_param_type *param);
static void boot_param_reset(void);
static void param_vaild_check(void);

void boot_param_handler(void)
{
    log_info("boot flash read...\r\n");
    boot_param_reset();
    boot_flash_read(sys_ops_api->flash_start_addr + sys_ops_api->param_offset_addr, (uint8_t *)&upgrade_param, sizeof(upgrade_param));
    param_vaild_check();
    report_param_info(&upgrade_param);

    // if (strcmp((char *)upgrade_param.bootloader_version, (char *)BOOT_VERSION))
    //     strncpy((void *)&upgrade_param.bootloader_version, BOOT_VERSION, sizeof(upgrade_param.bootloader_version));
    if (strcmp((char *)upgrade_param.bootloader_version, (char *)sys_ops_api->boot_version))
        strncpy((char *)&upgrade_param.bootloader_version, (char *)sys_ops_api->boot_version, sizeof(upgrade_param.bootloader_version));

    if (upgrade_param.running_safe_flag > 10)
    {
        upgrade_param.upgrade_flag = FW_UPGRADE_IN_BOOT;
        upgrade_param.running_safe_flag = 0;
    }
    else
    {
        upgrade_param.running_safe_flag++;
    }
    boot_param_write();
    report_param_info(&upgrade_param);

    if (upgrade_param.upgrade_flag == FW_UPGRADE_START)
    {
        upgrade_start_ack_msg();
    }
}

void boot_param_write(void)
{
    log_info("boot flash write...\r\n");
    upgrade_param.checksum = calc_crc_ccitt((uint8_t *)&upgrade_param, sizeof(upgrade_param) - 2);
    boot_flash_unlock();
    boot_flash_erase(sys_ops_api->flash_start_addr + sys_ops_api->param_offset_addr);
    boot_flash_write(sys_ops_api->flash_start_addr + sys_ops_api->param_offset_addr, (uint8_t *)&upgrade_param, sizeof(upgrade_param));
    boot_flash_lock();
}

static void report_param_info(upgrade_param_type *param)
{
    log_info("boot param report...\r\n");
    log_info("upgrade_flag: %x\r\n", param->upgrade_flag);
    log_info("running_safe_flag: %x\r\n", param->running_safe_flag);
    log_info("current boot version: %s\r\n", param->bootloader_version);
    log_info("current app version: %s\r\n", param->app_version);
    log_info("load_firmware_size: %lx\r\n", param->load_firmware_size);
}

static void boot_param_reset(void)
{
    upgrade_param.upgrade_flag = FW_UPGRADE_IN_BOOT;
    upgrade_param.running_safe_flag = 0;
}

static void param_vaild_check(void)
{
    uint16_t crc16_calc;

    crc16_calc = calc_crc_ccitt((uint8_t *)&upgrade_param, sizeof(upgrade_param) - 2);

    if (crc16_calc != upgrade_param.checksum)
    {
        if (upgrade_param.upgrade_flag > FW_UPGRADE_MAX)
        {
            if (upgrade_param.upgrade_flag == 0xFFFF)
                upgrade_param.upgrade_flag = FW_UPGRADE_NORMAL;
            else
                upgrade_param.upgrade_flag = FW_UPGRADE_IN_BOOT;
            upgrade_param.running_safe_flag = 0;
        }
    }

    boot_param_write();
}
