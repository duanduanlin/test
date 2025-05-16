#ifndef __HAL_BOOT_H__
#define __HAL_BOOT_H__

#include "protocol.h"
#include "boot_cfg.h"
#include <stdint.h>

#if USE_INTERFACE_CAN
#include "canard.h"
#endif

typedef enum
{
    CAN_PORT = 1,
    UART_PORT,
    USB_PORT,
} port_type_t;

typedef enum
{
    RX_FIFO = 1,
    TX_FIFO,
} fifo_num_t;

typedef struct iFrame
{
    uint64_t timestamp_usec;
    uint32_t id;
    uint32_t size;
    uint8_t data[8];
} iFrame_t;

typedef struct
{
    void (*unlock)(void);
    void (*lock)(void);
    void (*erase)(uint32_t);
    void (*read)(uint32_t, uint8_t *, uint16_t);
    void (*write)(uint32_t, uint8_t *, uint16_t);
} flash_ops_t;

typedef struct
{
    ringbuf_t *recv_fifo_ptr;
    ringbuf_t *send_fifo_ptr;
    int8_t (*ringbuf_is_empty)(ringbuf_t *);
    uint16_t (*ringbuf_get_payload_size)(ringbuf_t *);
    int8_t (*ringbuf_pop_bytes)(ringbuf_t *, void *, uint16_t len);
    int8_t (*ringbuf_push_bytes)(ringbuf_t *, const void *, uint16_t len);
} fifo_ops_t;

typedef struct
{
    uint8_t port_type;
    uint8_t module_self;
    uint16_t flash_param_max_size;
    uint16_t flash_app_max_size;
    uint32_t flash_start_addr;
    uint32_t param_offset_addr;
    uint32_t app_offset_addr;
    uint32_t ram_valid_addr_range;
    uint8_t boot_version[10];

    void (*reboot)(void);
    void (*reset)(void);
    void (*set_msp)(uint32_t);
    uint32_t (*get_sys_tick)(void);
    void (*delay_ms)(uint32_t);
    void (*task_led_callback)(void);
    void (*port_send_data)(uint8_t *, uint16_t);
#if USE_INTERFACE_CAN
    int8_t (*accept_canard_frame)(const CanardFrame *);
    uint8_t (*uavcan_msg_pack_publish)(CanardMicrosecond, CanardPortID, size_t, const void *);
#endif
} sys_ops_t;

typedef struct
{
    flash_ops_t *flash_ops;
    fifo_ops_t *fifo_ops;
    sys_ops_t *sys_ops;
} boot_ops_t;

void boot_init(boot_ops_t *ops);
void boot_run(void);

void boot_ops_init(boot_ops_t *ops);
void boot_flash_read(uint32_t addr, uint8_t *data, uint16_t len);
void boot_flash_write(uint32_t addr, uint8_t *data, uint16_t len);
void boot_flash_erase(uint32_t addr);
void boot_flash_unlock(void);
void boot_flash_lock(void);

uint8_t boot_get_port_type(void);

uint8_t boot_fifo_is_empty(uint8_t fifo_num);
uint16_t boot_fifo_payload_length(uint8_t fifo_num);
uint8_t boot_fifo_read(void *addr, uint16_t len, uint8_t fifo_num);
uint8_t boot_fifo_write(const void *addr, uint16_t len, uint8_t fifo_num);
#if USE_INTERFACE_CAN
uint8_t boot_uavcan_queue_can_send(const CanardFrame *txf);
#endif

sys_ops_t *boot_get_sys_ops_ptr(void);

#endif /* __HAL_BOOT_H__ */
