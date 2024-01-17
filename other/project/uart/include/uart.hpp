/*
 * @Author: dding3
 * @Date: 2022-12-06 14:29:22
 * @LastEditors: dding3
 * @LastEditTime: 2024-01-17 00:48:33
 * @Description:
 * @FilePath: /test/test/other/project/uart/include/uart.hpp
 */

#ifndef TEST_OTHER_PROJECT_UART_INCLUDE_UART_HPP_
#define TEST_OTHER_PROJECT_UART_INCLUDE_UART_HPP_

#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <thread>
#include <fcntl.h>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <termios.h>

class UartDev
{
public:
    /**
     * @brief 数据接收回调注册
     * @note
     * @param  &&fn:回调函数
     * @param  args: 参数列表
     * @retval None
     */
    template <class Fn, class... Args>
    void registerRecvCallback(Fn &&fn, Args &&...args);

    /**
     * @brief 开始接收
     * @note
     * @retval None
     */
    void startRecv();

    /**
     * @brief 停止接收
     * @note
     * @retval None
     */
    void stopRecv();
    /**
     * @brief 打开设备
     * @note
     * @param  *dev_name: 设备名
     * @param  baudRate: 波特率
     * @retval 返回设备操作符
     */
    int openUart(char *dev_name, int baudRate, int flow_ctrl = 0, int databits = 8, int parity = 'N', int stopbits = 1);

    /**
     * @brief 关闭设备
     * @note
     * @retval
     */
    bool closeUart(void);

    /**
     * @brief 数据发送
     * @note
     * @param  *data:待发送的数据
     * @param  len:数据长度
     * @retval
     */
    int sendData(uint8_t *data, int len);
    static UartDev &getInstance();

private:
    UartDev(void);
    virtual ~UartDev(void);

    UartDev(const UartDev &) = delete;
    UartDev &operator=(const UartDev &) = delete;

    /**
     * @brief 数据接收处理
     * @note
     * @retval None
     */
    void _waitRecv(void);

    /**
     * @description: 开启串口
     * @param {char} *filename
     * @return {*}成功返回fd，失败返回-1
     */
    int _uart_open(char *filename);

    /**
     * @description: 设置串口参数
     * @param {int} fd
     * @param {int} speed
     * @param {int} flow_ctrl
     * @param {int} databits
     * @param {int} parity
     * @param {int} stopbits
     * @return {*}
     */
    int _uart_set(int fd, int speed, int flow_ctrl, int databits, int parity, int stopbits);

private:
    int _fdUart;
    bool _recvFlag;
    std::mutex _mtxSend;
    std::function<int(uint8_t *, int)> _onRecv;
};

template <class Fn, class... Args>
void UartDev::registerRecvCallback(Fn &&fn, Args &&...args)
{
    _onRecv = std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...);
}

#endif // TEST_OTHER_PROJECT_UART_INCLUDE_UART_HPP_
