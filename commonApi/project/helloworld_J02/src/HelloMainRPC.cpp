/*
 * @Author: dding3
 * @Date: 2023-07-27 11:13:03
 * @LastEditors: dding3
 * @LastEditTime: 2023-08-22 02:28:58
 * @Description:
 * @FilePath: /test/commonapi/test/commonApi/project/helloworld/src/HelloMainRPC.cpp
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>

int main()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    while (true)
    {
        std::cout << "Hello world" << "\r\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
