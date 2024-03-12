/*
 * @Author: dding3
 * @Date: 2024-02-22 17:52:08
 * @LastEditors: dding3
 * @LastEditTime: 2024-02-22 17:56:12
 * @Description:
 * @FilePath: /test/test/someIP/project/iweather/src/someip_server.cpp
 */
#include <string>
#include <csignal>
#include <unistd.h>
#include "CommonAPI/CommonAPI.hpp"
#include "v0/com/commapi/test/IWeatherServiceStubDefault.hpp"

using namespace v0::com::commapi::test;

class WeatherServiceStub : public IWeatherServiceStubDefault {
private:
    int temp = -32;
public:
    WeatherServiceStub() = default;
     ~WeatherServiceStub() override = default;
    void getTemp(const std::shared_ptr<CommonAPI::ClientId> _client, getTempReply_t _reply) override{
        printf("%s : gid[%d], uid[%d]\n", __func__ , _client->getGid(), _client->getUid());
        _reply(temp++);
    }
};

int main(int args, char** argc){
    //设置配置文件路径
    setenv("COMMONAPI_CONFIG", "/etc/commonapi.ini",1);
    setenv("VSOMEIP_CONFIGURATION", "/etc/local_server.json", 1);
    auto runtime = CommonAPI::Runtime::get();
    auto weather_service = std::make_shared<WeatherServiceStub>();
    auto server_register = runtime->registerService("local",
                                           "com.commapi.test.IWeatherService",
                                           weather_service,
                                           "someip_server");
    printf("register weather service : %d\n", server_register);
    while(true){
        usleep(1000 * 1000);
    }
    return 1;
}
