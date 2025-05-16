#ifndef __FLASH_H__
#define __FLASH_H__

#include <stdint.h>

void flash_erase(uint32_t addr);
void flash_read_bytes(uint32_t addr, uint8_t *data, uint16_t len);
void flash_program_prepare(void);
void flash_program(uint32_t addr, uint8_t *data, uint16_t len);
void flash_program_finish(void);
void flash_write_bytes(uint32_t addr, uint8_t *data, uint32_t len);

int stmflash_test();
#endif /* __FLASH_H__ */
