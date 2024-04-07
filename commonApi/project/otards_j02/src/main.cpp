/*
 * @Author: dding3
 * @Date: 2023-07-27 11:13:03
 * @LastEditors: dding3 dding3@jmc.com.cn
 * @LastEditTime: 2024-04-01 19:03:28
 * @Description:
 * @FilePath: /test/test/commonApi/project/otards_j02/src/main.cpp
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>
#include "ota_tbox_helper.h"
#include "log.hpp"

char test_ota_get_handbrake_state(char **argv)
{
    unsigned char handbrake_state = 0;
    printf("call ota_get_handbrake_state\r\n");
    int res = ota_get_handbrake_state(&handbrake_state);
    printf("test_ota_get_handbrake_state res = %d handbrake_state = %d\n", res, handbrake_state);
    return res;
}

// ---- get memory info ---- //
void getMemoryInfo()
{
    FILE *fp = fopen("/proc/meminfo", "r");
    if (NULL == fp)
        printf("failed to open meminfo\n");
    char szTest[1000] = {0};
    while (!feof(fp))
    {
        memset(szTest, 0, sizeof(szTest));
        fgets(szTest, sizeof(szTest) - 1, fp);
        printf("%s", szTest);
    }
    fclose(fp);
}

int main()
{
    if (test_ota_get_handbrake_state(nullptr) == 0)
    {
        printf("otards test success\t\n");
    }
    else
    {
        printf("otards test failed\t\n");
        system("echo 0 > /tmp/testFailed");
    }
    // getMemoryInfo();
    // while (true)
    // {
    //     // printf("start test\r\n");
    //     test_ota_get_handbrake_state(nullptr);
    //     // printf("done\r\n");
    //     std::this_thread::sleep_for(std::chrono::seconds(5));
    // }
    return 0;
}
