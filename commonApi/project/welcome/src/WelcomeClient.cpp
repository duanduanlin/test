/*
 * @Author: dding3
 * @Date: 2023-07-27 11:13:03
 * @LastEditors: dding3
 * @LastEditTime: 2023-07-28 13:43:02
 * @Description:
 * @FilePath: \test\commonApi\project\welcome\src\WelcomeClient.cpp
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/welcome/WelcomeProxy.hpp>

using namespace v1_0::welcome;

std::shared_ptr<WelcomeProxy<>> myProxy = nullptr;

void _welcome(std::string message)
{
    std::string returnMessage;
    CommonAPI::CallStatus callStatus;
    std::cout << message << std::endl;
    myProxy->sayHi("Hi,i'm Bob", callStatus,returnMessage);
    std::cout << "Got message: '" << returnMessage << "'\n";
}

int main()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    myProxy = runtime->buildProxy<WelcomeProxy>("local", "test");

    myProxy->getWelcomeEvent().subscribe(_welcome);
    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
