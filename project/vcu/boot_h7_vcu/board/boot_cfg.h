#ifndef __BOOT_CFG_H__
#define __BOOT_CFG_H__

// header file

// port
#define USE_INTERFACE_CAN 0
#define USE_INTERFACE_UART 1

// ringbuf data type
#define ringbuf_t void

// log info
#define log_info(format, ...) printf(format, ##__VA_ARGS__)

#endif /* __BOOT_CFG_H__ */
