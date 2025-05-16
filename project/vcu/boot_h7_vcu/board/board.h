#ifndef __BOARD_H__
#define __BOARD_H__

#include "dma.h"
#include "gpio.h"
#include "hal_boot.h"
#include "port_canard.h"
#include "flash.h"

void board_init(void);
extern uint8_t uart_rec_buf[512];

void reset_uart_rec(void);

#endif /* __BOARD_H__ */
