/*
 * @Author: dding3
 * @Date: 2023-07-27 14:53:49
 * @LastEditors: dding3
 * @LastEditTime: 2023-07-28 13:40:07
 * @Description:
 * @FilePath: \test\commonApi\project\welcome\src\WelcomeService.cpp
 */
#include <iostream>
#include <thread>
#include <CommonAPI/CommonAPI.hpp>
#include "WelcomeStubImpl.hpp"

using namespace std;

int main()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<WelcomeStubImpl> myService =
        std::make_shared<WelcomeStubImpl>();
    runtime->registerService("local", "test", myService);
    std::cout << "Successfully Registered Service!" << std::endl;

    while (true)
    {
        myService->fireWelcomeEvent("welcome!");
        std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    return 0;
}
