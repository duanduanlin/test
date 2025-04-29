#ifndef __CRC16_H
#define __CRC16_H

#include <stdint.h>

uint16_t calc_crc_ccitt(uint8_t *buf, int len);
uint16_t calc_crc16_table(uint8_t *ptr, uint16_t len);
uint8_t calc_checksum(const uint8_t *ptr, uint16_t len);

#endif /* __CRC16_H */
