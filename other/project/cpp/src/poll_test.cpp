/*
 * @Author: dding3
 * @Date: 2023-12-13 17:51:25
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-13 17:52:06
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/poll_test.cpp
 */
#include <iostream>
#include <poll.h>
#include <unistd.h>

int main()
{
    // 创建 pollfd 数组
    struct pollfd fds[1];

    // 添加需要监听的套接字到 pollfd 数组中
    fds[0].fd = STDIN_FILENO; /* 套接字文件描述符 */
    fds[0].events = POLLIN; // 监听可读事件

    // 开始监听事件
    while (true)
    {
        int ret = poll(fds, 1, -1);
        if (ret > 0)
        {
            if (fds[0].revents & POLLIN)
            {
                // 可读事件发生在套接字上
                char buffer[256];
                ssize_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
                if (bytesRead > 0)
                {
                    buffer[bytesRead] = '\0';
                    std::cout << "Received input: " << buffer << std::endl;
                }
            }
        }
        else if (ret == -1)
        {
            std::cerr << "Error while polling" << std::endl;
            break;
        }
    }

    return 0;
}
