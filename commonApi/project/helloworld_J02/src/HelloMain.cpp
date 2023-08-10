/*
 * @Author: dding3
 * @Date: 2023-07-27 11:13:03
 * @LastEditors: dding3
 * @LastEditTime: 2023-08-09 00:53:05
 * @Description:
 * @FilePath: /test/commonapi/test/commonApi/project/helloworld/src/HelloMain.cpp
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <thread>


int main()
{
    while (true)
    {
        std::cout << "Hello world" << "\r\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
