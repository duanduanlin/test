/*
 * @Author: dding3
 * @Date: 2023-12-18 18:11:27
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-18 18:24:49
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/select_test.cpp
 */
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void test_break(int *fd)
{
    *fd = open("test.txt", O_RDONLY);
}

int main()
{
    int fd;
    fd_set fds;
    struct timeval tv;
    int err;
    int i = 0;

    while (1)
    {
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 200 * 1000; // 1s;单位：us, 1ms = 1000us;

        err = select(fd + 1, &fds, NULL, NULL, &tv);
        // 如果tv为0，则无限超时阻塞
        // err = select(FD_SETSIZE, &fds, (fd_set *)0,(fd_set *)0, (struct timeval *) 0);
        if (err == 0)
        {
            printf("select time out 200 ms!\n");
            i++;
            if (i == 5)
                test_break(&fd);
        }
        else if (err == -1)
        {
            printf("fail to select!\n");
            break;
        }
        else
        {
            int ret;
            char buf[32] = {0};

            printf("data is available!\n");
            ret = read(fd, buf, 10);
            printf("buf = %s\n", buf);
            if (ret <= 0)
            {
                close(fd);
                break;
            }
        }
    }
    return 0;
}
