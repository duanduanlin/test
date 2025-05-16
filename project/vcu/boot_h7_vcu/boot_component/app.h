#ifndef __APP_H__
#define __APP_H__

#include "hal_boot.h"
#include "protocol.h"
#include "bl.h"
#include "com.h"
#include "led.h"
#include "param.h"
#include "crc16.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct timer_pcb
{
    uint32_t tick;
};

extern sys_ops_t *sys_ops_api;

int is_run_time(struct timer_pcb *p, uint32_t period);

#endif /* __APP_H__ */
