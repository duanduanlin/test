/*
 * @Author: dding3
 * @Date: 2023-07-27 14:53:49
 * @LastEditors: dding3
 * @LastEditTime: 2023-07-27 16:59:38
 * @Description:
 * @FilePath: \test\commonApi\project\goodbye\src\GoodByeService.cpp
 */
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "GoodByeStubImpl.hpp"

using namespace std;

int main()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<GoodByeStubImpl> myService =
        std::make_shared<GoodByeStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    while (true)
    {
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(30));
    }
    return 0;
}
