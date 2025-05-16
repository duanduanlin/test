#ifndef __BL_H__
#define __BL_H__

#include <stdint.h>

void task_port_msg_recv(void);
void app_ota_msg_handler(uint8_t cmd, uint8_t *pd, uint16_t len);
void task_bootloader_entry(uint32_t period);

void upgrade_start_ack_msg(void);
void task_uavcan_test_entry(uint32_t period);

#endif /* __BL_H__ */
