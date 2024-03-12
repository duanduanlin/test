/*
 * @Author: dding3
 * @Date: 2024-02-22 18:49:10
 * @LastEditors: dding3
 * @LastEditTime: 2024-02-26 23:09:02
 * @Description:
 * @FilePath: /test/test/someIP/project/vsomeIpVbox/src/someip_client.cpp
 */
#include <string>
#include <vsomeip/vsomeip.hpp>
#include <csignal>
#include <unistd.h>
#include "thread"

static vsomeip::service_t  weather_service_id = 0x1001;
static vsomeip::instance_t weather_service_instance_id = 0x0001;
static vsomeip::method_t   weather_get_temp_method_id = 0x0001;
static vsomeip::method_t weather_get_mois_method_id = 0x0002;

int main(int args, char** argc){
    //setenv("VSOMEIP_CONFIGURATION", "/etc/local_client.json", 1);
    auto rtm_ = vsomeip::runtime::get();
    auto app_ = rtm_->create_application("someip_client");
    if(!app_->init()){
        printf("init failed\n");
        return 0;
    }

    app_->register_message_handler(weather_service_id,
                                   weather_service_instance_id,
                                   weather_get_temp_method_id,
                                   [](const std::shared_ptr<vsomeip::message>& msg){
                                       printf("MessageCallback : %s\n",msg->get_payload()->get_data());
    });

    app_->register_availability_handler(weather_service_id,
                                        weather_service_instance_id,
                                        [&app_, &rtm_](vsomeip::service_t service, vsomeip::instance_t instance, bool available){
                                            printf("AvailableHandler : service = 0x%02x, instance = 0x%02x , available = %d\n",
                                                   service,
                                                   instance,
                                                   available ? 1 : 0);
                                            if(available){
                                                std::thread send([&rtm_, &app_]{
                                                    int count = 10;
                                                    while(count -- > 0) {
                                                        printf("send::\n");
                                                        auto msg = rtm_->create_request(true);
                                                        msg->set_service(weather_service_id);
                                                        msg->set_instance(weather_service_instance_id);
                                                        msg->set_method(weather_get_temp_method_id);
                                                        std::vector<vsomeip::byte_t> payload_raw = {0x0, 0x0 , static_cast<unsigned char>(count)};
                                                        auto payload = rtm_->create_payload(payload_raw);
                                                        msg->set_payload(payload);
                                                        app_->send(msg);
                                                        usleep(1000 * 1000);
                                                    }
                                                    while(count++ <10)
                                                    {
                                                        printf("send::\n");
                                                        auto msg = rtm_->create_request(true);
                                                        msg->set_service(weather_service_id);
                                                        msg->set_instance(weather_service_instance_id);
                                                        msg->set_method(weather_get_mois_method_id);
                                                        std::vector<vsomeip::byte_t> payload_raw = {0x0, 0x0 , static_cast<unsigned char>(count)};
                                                        auto payload = rtm_->create_payload(payload_raw);
                                                        msg->set_payload(payload);
                                                        app_->send(msg);
                                                        usleep(1000 * 1000);
                                                    }
                                                });
                                                send.detach();
                                            }
    });

    app_->register_state_handler([&app_](vsomeip::state_type_e state){
        if(state == vsomeip::state_type_e::ST_REGISTERED){
            app_->request_service(weather_service_id, weather_service_instance_id);
        }
    });

    app_->start();

    while(true){
        usleep(1000 * 1000);
    }
    return 1;
}
