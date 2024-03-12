#include <string>
#include <csignal>
#include <unistd.h>
#include "thread"
#include "CommonAPI/CommonAPI.hpp"
#include "v0/com/commapi/test/IWeatherService.hpp"
#include "v0/com/commapi/test/IWeatherServiceProxy.hpp"

using namespace v0::com::commapi::test;

int main(int args, char** argc){
    setenv("COMMONAPI_CONFIG", "/etc/commonapi.ini",1);
    setenv("VSOMEIP_CONFIGURATION", "/etc/local_client.json", 1);
    auto runtime = CommonAPI::Runtime::get();
    auto app = runtime->buildProxy<IWeatherServiceProxy>("local",
                                                         "com.commapi.test.IWeatherService",
                                                         "someip_client");
    while(true){
        if(!app->isAvailable()){
            printf("connecting failed, retry\n");
            sleep(1);
            continue;
        }
        break;
    }
    app->getProxyStatusEvent().subscribe([&app](CommonAPI::AvailabilityStatus status){
        if(status == CommonAPI::AvailabilityStatus::AVAILABLE){
            printf("service available\n");
            std::thread t1([&app]{
                for(int i=0; i<10; i++){
                    CommonAPI::CallStatus callStatus;
                    int32_t temp;
                    CommonAPI::CallInfo callInfo;
                    app->getTemp(callStatus, temp, &callInfo);
                    printf("CallStatus = %d, getTemp: %d\n",callStatus, temp);
                }
            });
            t1.detach();
        }
    });

    while(true){
        usleep(1000 * 1000);
    }
    return 1;
}
