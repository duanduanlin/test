#ifndef __CAN_DRIVER_H__
#define __CAN_DRIVER_H__

#include "stdint.h"

int can_send_msg(uint32_t id, const uint8_t *data, uint8_t len);

#endif 
