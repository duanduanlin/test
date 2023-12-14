/*
 * @Author: dding3
 * @Date: 2023-12-13 17:59:19
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-13 17:59:28
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/epoll_test.cpp
 */
#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>

#define MAX_EVENTS 10
#define MAX_BUF_SIZE 1024

int main()
{
    int epoll_fd, event_count;
    struct epoll_event event, events[MAX_EVENTS];
    char buffer[MAX_BUF_SIZE];

    // 创建epoll句柄
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1)
    {
        std::cerr << "Failed to create epoll file descriptor." << std::endl;
        return 1;
    }

    // 设置监听的文件描述符
    event.data.fd = STDIN_FILENO; // 监听标准输入
    event.events = EPOLLIN;       // 监听可读事件

    // 将监听事件添加到epoll句柄中
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1)
    {
        std::cerr << "Failed to add file descriptor to epoll." << std::endl;
        close(epoll_fd);
        return 1;
    }

    while (true)
    {
        // 等待事件发生
        event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (event_count == -1)
        {
            std::cerr << "Failed to wait for events." << std::endl;
            close(epoll_fd);
            return 1;
        }

        // 处理所有发生的事件
        for (int i = 0; i < event_count; ++i)
        {
            // 如果是标准输入可读事件
            if (events[i].data.fd == STDIN_FILENO)
            {
                // 读取用户输入
                int read_count = read(STDIN_FILENO, buffer, MAX_BUF_SIZE);
                if (read_count == -1)
                {
                    std::cerr << "Failed to read from standard input." << std::endl;
                    close(epoll_fd);
                    return 1;
                }
                // 将读取到的内容打印出来
                std::cout << "Read from standard input: " << buffer << std::endl;
            }
        }
    }

    // 关闭epoll句柄
    close(epoll_fd);
    return 0;
}
