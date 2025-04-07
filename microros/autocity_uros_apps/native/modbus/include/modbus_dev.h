#ifndef NATIVE_MODBUS_INCLUDE_MODBUS_DEV_H_
#define NATIVE_MODBUS_INCLUDE_MODBUS_DEV_H_

#include "stdint.h"
#ifdef __cplusplus
extern "C"
{
#endif

    int modbus_dev_read_registers(int add, int len, uint16_t*data);

    int modbus_dev_init(const char *dev, int bitrates, int add);

    int modbus_dev_deinit();

#ifdef __cplusplus
}
#endif

#endif // NATIVE_MODBUS_INCLUDE_MODBUS_DEV_H_
