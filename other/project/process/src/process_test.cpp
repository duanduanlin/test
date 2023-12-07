/*
 * @Author: dding3
 * @Date: 2023-12-06 19:00:53
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-06 19:03:54
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/process/src/process_test.cpp
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
    pid_t pid = getpid();
    char strProcessPath[1024] = {0};
    if (readlink("/proc/self/exe", strProcessPath, 1024) <= 0)
    {
        return -1;
    }

    char *strProcessName = strrchr(strProcessPath, '/');

    if (!strProcessName)
    {
        printf("curr process ID:%d\n", pid);
        printf("curr process name\n");
        printf("curr process path:%s\n", strProcessPath);
    }
    else
    {
        printf("curr process ID:%d\n", pid);
        printf("curr process name: %s\n", ++strProcessName);
        printf("curr process path:%s\n", strProcessPath);
    }

    return 0;
}
