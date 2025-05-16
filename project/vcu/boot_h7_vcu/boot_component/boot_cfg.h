#ifndef __BOOT_CFG_H__
#define __BOOT_CFG_H__

// header file
#include "ring_buffer.h"

// port
#define USE_INTERFACE_CAN 1
#define USE_INTERFACE_UART 0

// ringbuf data type
#define ringbuf_t mrb_t

// log info
#define log_info(format, ...) printf(format, ##__VA_ARGS__)

#endif /* __BOOT_CFG_H__ */
