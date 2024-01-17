/*
 * @Author: dding3
 * @Date: 2024-01-17 00:39:20
 * @LastEditors: dding3
 * @LastEditTime: 2024-01-17 00:50:52
 * @Description:
 * @FilePath: /test/test/other/project/uart/src/main.cpp
 */
#include "uart.hpp"

#define UART_DEV_NAME "/dev/ttyUSB3"
#define UART_BAUDRATE 460800

static int _onDataRecv(uint8_t *data, int len)
{
    printf("got some data len:%d\r\n", len);
    return 0;
}

int main()
{
    UartDev::getInstance().registerRecvCallback(&_onDataRecv, std::placeholders::_1, std::placeholders::_2);
    if (UartDev::getInstance().openUart((char *)UART_DEV_NAME, UART_BAUDRATE) > 0)
    {
        printf("McuHal init done\r\n");
        UartDev::getInstance().startRecv();
    }
    else
    {
        printf("uart:%s open failed\r\n", UART_DEV_NAME);
    }

    uint8_t data[] = {0xAA,0x77,0x01,0xD2,0xBF,0xD2,0x01,0x00,0x09,0x12,0x34,0x07,0x01,0x24,0xCC,0x07,0x02,0x7A};

    UartDev::getInstance().sendData(data, sizeof(data));

    sleep(1);
    UartDev::getInstance().stopRecv();
    UartDev::getInstance().closeUart();
    return 0;
}
