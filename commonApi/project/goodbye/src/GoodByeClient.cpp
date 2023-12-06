/*
 * @Author: dding3
 * @Date: 2023-07-27 11:13:03
 * @LastEditors: dding3
 * @LastEditTime: 2023-07-28 10:32:13
 * @Description:
 * @FilePath: \test\commonApi\project\goodbye\src\GoodByeClient.cpp
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/good_bye/GoodByeProxy.hpp>
#include <v1/hello_world/HelloWorldProxy.hpp>

using namespace v1_0::good_bye;
using namespace v1_0::hello_world;

int main()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<GoodByeProxy<>> goodByeProxy =
        runtime->buildProxy<GoodByeProxy>("local", "test");
    std::shared_ptr<HelloWorldProxy<>> helloWorldProxy =
        runtime->buildProxy<HelloWorldProxy>("local", "test");

    std::cout << "Checking availability!" << std::endl;
    while (!goodByeProxy->isAvailable() || !helloWorldProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    while (true)
    {
        helloWorldProxy->sayHello("Tom", callStatus, returnMessage);
        std::cout << "Got message: '" << returnMessage << "'\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
        goodByeProxy->sayGoodBye("Tom", callStatus, returnMessage);
        std::cout << "Got message: '" << returnMessage << "'\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
