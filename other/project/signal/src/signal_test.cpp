/*
 * @Author: dding3
 * @Date: 2023-12-06 18:25:08
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-06 18:27:27
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/signal/src/signal_test.cpp
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig)
{
    printf("hello:%d\n", sig);
}

main()
{
    int i;
    signal(SIGALRM, handler);
    alarm(5);
    for (i = 1; i < 7; i++)
    {
        printf("sleep %d ...\r\n", i);
        sleep(1);
    }
}
