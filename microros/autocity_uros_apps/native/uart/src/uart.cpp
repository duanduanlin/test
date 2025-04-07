/*
 * @Author: dding3
 * @Date: 2022-12-06 14:42:30
 * @LastEditors: dding3
 * @LastEditTime: 2024-01-17 19:07:44
 * @Description:
 * @FilePath: /test/test/other/project/uart/src/uart.cpp
 */
#include "uart.hpp"

const int UART_BUFF_LEN = 256;

static int speed_arr[] = {B1500000, B1152000, B1000000, B921600,
                          B576000, B500000, B460800, B230400, B115200, B57600,
                          B38400, B19200, B9600, B4800, B2400, B1800, B1200,
                          B600, B300, B200, B150, B134, B110, B75, B50, B0};

static int name_arr[] = {1500000, 1152000, 1000000, 921600,
                         576000, 500000, 460800, 230400, 115200, 57600,
                         38400, 19200, 9600, 4800, 2400, 1800, 1200,
                         600, 300, 200, 150, 134, 110, 75, 50, 0};

UartDev &UartDev::getInstance()
{
    static UartDev ud;
    return ud;
}

UartDev::UartDev(void)
    : _fdUart(-1), _recvFlag(false), _onRecv(nullptr)
{
    std::thread recvWaitThread(&UartDev::_waitRecv, this);
    recvWaitThread.detach();
}

UartDev::~UartDev(void)
{
    if (_fdUart >= 0)
    {
        closeUart();
    }
}

void UartDev::startRecv()
{
    _recvFlag = true;
}

void UartDev::stopRecv()
{
    _recvFlag = false;
}

int UartDev::openUart(char *dev_name, int baudRate, int flow_ctrl, int databits, int parity, int stopbits)
{
    _fdUart = _uart_open(dev_name);
    if (_fdUart >= 0)
    {
        if (_uart_set(_fdUart, baudRate, flow_ctrl, databits, parity, stopbits) == 0)
        {
            printf("uart open success\r\n");
        }
        else
        {
            close(_fdUart);
            _fdUart = -1;
        }
    }
    return _fdUart;
}

int UartDev::sendData(uint8_t *data, int len)
{
    int ret = -1;
    int count = 0;
    int tryTimes = 0;

    if (_fdUart < 0)
    {
        printf("uart dev is not open\r\n");
        return -1;
    }

    _mtxSend.lock();
    if (_fdUart >= 0)
    {
        while (count < len)
        {
            ret = ::write(_fdUart, (const char *)data + count, len - count);
            if (ret <= 0)
            {
                if (tryTimes > 20)
                {
                    printf("something got wrong\r\n");
                    break;
                }
                //logi("uart write tryTimes:%d, ret:%d\r\n", tryTimes, ret);
                tryTimes++;
                usleep(1000 * 10); // 缓存可能满了，稍微等待下
            }
            else
            {
                tryTimes = 0; //重试次数清零
                count += ret;
            }
        }
    }
    _mtxSend.unlock();
    // printf("uart write %d Bytes,ret:%d\r\n", len, count);

    return ret;
}

void UartDev::_waitRecv(void)
{
    int iRet;
    fd_set fdset;
    int read_cnt = 0;
    struct timeval timeout = {1, 0}; // timeout 1s
    char buffer[UART_BUFF_LEN] = {0};
    printf("_waitRecv thread created\r\n");
    while (1)
    {
        if (_fdUart < 0 || _recvFlag == false)
        {
            sleep(1);
            continue;
        }

        FD_ZERO(&fdset);
        FD_SET(_fdUart, &fdset);
        iRet = select(_fdUart + 1, &fdset, NULL, NULL, &timeout);
        if (-1 == iRet)
        {
            printf("failed to select\r\n");
        }
        else if (0 == iRet)
        {
            // no data in Rx buffer
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;
        }
        else
        {
            // data is in Rx data
            if (FD_ISSET(_fdUart, &fdset))
            {
                read_cnt = 0;
                do
                {
                    memset(buffer, 0x0, sizeof(buffer));
                    iRet = read(_fdUart, buffer, UART_BUFF_LEN);
                    if (iRet > 0)
                    {
                        read_cnt = read_cnt + iRet;
                        if (_onRecv != nullptr)
                        {
                            _onRecv((uint8_t *)buffer, iRet);
                        }
                    }
                } while (_fdUart >= 0 && _recvFlag && UART_BUFF_LEN == iRet);
            }
        }
    }
    printf("_waitRecv thread will be destroy\r\n");
    return;
}

bool UartDev::closeUart(void)
{
    _recvFlag = false;
    if (_fdUart <= 0)
    {
        printf("uart_close : fd:%d\r\n", _fdUart);
        return false;
    }

    if (close(_fdUart) >= 0)
    {
        _fdUart = -1;
        printf("close uart!\r\n");
    }
    else
    {
        printf("close failed(%s)\r\n", strerror(errno));
    }

    return _fdUart == -1;
}

int UartDev::_uart_open(char *filename)
{
    int fd;

    fd = open(filename, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0)
    {
        printf("%s %d: failed to open serial %s\n", __FILE__, __LINE__, filename);
        return -1;
    }

    // nonblock
    if (fcntl(fd, F_SETFL, 0) < 0)
    {
        printf("fcntl failed\n");
        close(fd);
        return -1;
    }
    return fd;
}

int UartDev::_uart_set(int fd, int speed, int flow_ctrl, int databits, int parity, int stopbits)
{
    struct termios options;
    int ret = 0;

    memset(&options, 0, sizeof(options));
    if (tcgetattr(fd, &options) != 0)
    {
        printf("tcgetattr serial fialed!\n");
        return -1;
    }

    cfmakeraw(&options);

    options.c_cflag |= CREAD;

    for (int i = 0; i < sizeof(speed_arr) / sizeof(int); i++)
    {
        if (speed == name_arr[i])
        {
            ret = cfsetispeed(&options, speed_arr[i]);
            if (ret)
            {
                printf("set in speed failed\n");
                return -1;
            }

            ret = cfsetospeed(&options, speed_arr[i]);
            if (ret)
            {
                printf("set out speed failed\n");
                return -1;
            }
            break;
        }
    }

    options.c_cflag &= ~CSIZE;
    switch (databits)
    {
    case 5:
        options.c_cflag |= CS5;
        break;
    case 6:
        options.c_cflag |= CS6;
        break;
    case 7:
        options.c_cflag |= CS7;
        break;
    case 8:
        options.c_cflag |= CS8;
        break;
    default:
        printf("Unsupported databits!\n");
        return -1;
    }

    switch (parity)
    {
    case 'n': // no parity
    case 'N':
        options.c_cflag &= ~PARENB;
        options.c_iflag &= ~INPCK;
        break;
    case 'o': // odd parity
    case 'O':
        options.c_cflag |= (PARODD | PARENB);
        options.c_iflag &= INPCK;
        break;
    case 'e': // even parity
    case 'E':
        options.c_cflag |= PARENB;
        options.c_cflag &= ~PARODD;
        options.c_iflag |= INPCK;
        break;
    case 's': // blank
    case 'S':
        options.c_cflag &= ~PARENB;
        options.c_iflag &= ~CSTOPB;
        break;
    default:
        printf("Unsupported parity\n");
        return -1;
    }

    switch (stopbits)
    {
    case 1:
        options.c_cflag &= ~CSTOPB;
        break;
    case 2:
        options.c_cflag |= CSTOPB;
        break;
    default:
        printf("Unsupported stop bits\n");
        return -1;
    }

    switch (flow_ctrl)
    {
    case 0: // no flow control
        options.c_cflag &= ~CRTSCTS;
        break;
    case 1: // hardware flow control
        options.c_cflag |= CRTSCTS;
        break;
    case 2: // software flow control
        options.c_cflag |= IXON | IXOFF | IXANY;
        break;
    default:
        printf("Unsupported flow control\n");
        return -1;
    }

    options.c_cc[VTIME] = 0;
    options.c_cc[VMIN] = 0;

    // if data overflow, receive data, but not read
    tcflush(fd, TCIFLUSH);

    // save configuration
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
        printf("set serial error!\n");
        return -1;
    }
    return 0;
}
