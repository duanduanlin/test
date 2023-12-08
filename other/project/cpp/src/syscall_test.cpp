/*
 * @Author: dding3
 * @Date: 2023-12-07 18:57:03
 * @LastEditors: dding3
 * @LastEditTime: 2023-12-07 19:02:14
 * @Description:
 * @FilePath: /test/commonapi/test/other/project/cpp/src/syscall_test.cpp
 */
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <sys/syscall.h>

int main()
{
    struct timeval tv;
    int result;

    result = syscall(SYS_time, &tv, NULL);
    if (result == 0)
    {
        std::cout << "timestmp:" << tv.tv_sec << std::endl;
    }
    else
    {
        std::cout << "get time failed:" << result << std::endl;
    }

    return 0;
}
