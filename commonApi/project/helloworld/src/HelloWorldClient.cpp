/*
 * @Author: dding3
 * @Date: 2023-07-27 11:13:03
 * @LastEditors: dding3
 * @LastEditTime: 2023-08-22 02:29:15
 * @Description:
 * @FilePath: /test/commonapi/test/commonApi/project/helloworld/src/HelloWorldClient.cpp
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/hello_world/HelloWorldProxy.hpp>

using namespace v1_0::hello_world;

int main()
{
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    std::shared_ptr<HelloWorldProxy<>> myProxy =
        runtime->buildProxy<HelloWorldProxy>("local", "test");

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        usleep(10);
    std::cout << "Available..." << std::endl;

    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    while (true)
    {
        myProxy->sayHello("Bob", callStatus, returnMessage);
        std::cout << "Got message: '" << returnMessage << "'\n";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}
