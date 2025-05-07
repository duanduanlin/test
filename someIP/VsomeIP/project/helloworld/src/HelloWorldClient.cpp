/*
 * @Author: dding3
 * @Date: 2023-07-27 11:13:03
 * @LastEditors: dding3
 * @LastEditTime: 2024-02-22 01:44:07
 * @Description:
 * @FilePath: /test/test/someIP/project/helloworld/src/HelloWorldClient.cpp
 */
#include <iostream>
#include <string>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/hello_world/HelloWorldProxy.hpp>

using namespace v1_0::hello_world;

int main()
{
   std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.HelloWorld";
    std::string connection = "client-sample";

    std::shared_ptr<HelloWorldProxy<>> myProxy = runtime->buildProxy<HelloWorldProxy>(domain,
            instance, connection);

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    std::cout << "Available..." << std::endl;

    const std::string name = "World";
    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    CommonAPI::CallInfo info(1000);
    info.sender_ = 1234;

    while (true) {
        myProxy->sayHello(name, callStatus, returnMessage, &info);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            std::cerr << "Remote call failed!\n";
            return -1;
        }
        info.timeout_ = info.timeout_ + 1000;

        std::cout << "Got message: '" << returnMessage << "'\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
