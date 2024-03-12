/*
 * @Author: dding3
 * @Date: 2023-07-27 11:13:03
 * @LastEditors: dding3
 * @LastEditTime: 2024-03-11 00:16:54
 * @Description:
 * @FilePath: /test/test/commonApi/project/otards_j02/src/main.cpp
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>
#include "ota_tbox_helper.h"
#include "log.hpp"

char test_ota_get_handbrake_state(char **argv){
        unsigned char handbrake_state = 0;
        logi("call ota_get_handbrake_state\r\n");
        int res = ota_get_handbrake_state(&handbrake_state);
        logi("test_ota_get_handbrake_state res = %d handbrake_state = %d\n",res,handbrake_state);
        return res;
}

int main()
{
    if(test_ota_get_handbrake_state(nullptr) == 0)
    {
        printf("otards test success\t\n");
    }else{
        printf("otards test failed\t\n");
        system("echo 0 > /tmp/testFailed");
    }
    // while (true)
    // {
    //     // printf("start test\r\n");
    //     test_ota_get_handbrake_state(nullptr);
    //     // printf("done\r\n");
    //     std::this_thread::sleep_for(std::chrono::seconds(5));
    // }
    return 0;
}
