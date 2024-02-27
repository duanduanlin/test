/*
 * @Author: dding3
 * @Date: 2024-02-22 18:47:46
 * @LastEditors: dding3
 * @LastEditTime: 2024-02-26 23:06:35
 * @Description:
 * @FilePath: /test/test/someIP/project/vsomeIpVbox/src/someip_server.cpp
 */
#include <string>
#include <vsomeip/vsomeip.hpp>
#include <csignal>
#include <unistd.h>

//服务ID
static vsomeip::service_t  weather_service_id = 0x1001;
//服务实例ID
static vsomeip::instance_t weather_service_instance_id = 0x0001;
//方法ID
static vsomeip::method_t weather_get_temp_method_id = 0x0001;
static vsomeip::method_t weather_get_mois_method_id = 0x0002;

static std::shared_ptr<vsomeip::application> app_;

//处理message消息
static void on_message_callback(const std::shared_ptr<vsomeip::message>& msg){
    printf("%s message = ", __func__);
    vsomeip::byte_t *data = msg->get_payload()->get_data();
    for(int i=0; i< msg->get_payload()->get_length(); i++){
        printf("%02x ", data[i]);
    }
    printf("\n");
}

//处理状态消息
static void on_state_callback(vsomeip::state_type_e state){
    printf("%s state = %hhu\n", __func__ , state);
    if(state == vsomeip::state_type_e::ST_REGISTERED){
        app_->offer_service(weather_service_id, weather_service_instance_id);
    }
}

int main(int args, char** argc){
    //设置配置文件路径
    //setenv("VSOMEIP_CONFIGURATION", "/etc/local_server.json", 1);
    //获取vsomeip运行环境
    auto rtm_ = vsomeip::runtime::get();
    //创建一个vsomeip app
    app_ = rtm_->create_application("someip_server");
    //初始化
    if(!app_->init()){
        return 0;
    }

    //初始花完成后，注册消息回调，event, method，以及attribute的set，get,notify等消息都是走这里
    app_->register_message_handler(weather_service_id,
                                   weather_service_instance_id,
                                   weather_get_temp_method_id,
                                   &on_message_callback);

    app_->register_message_handler(weather_service_id,
                                   weather_service_instance_id,
                                   weather_get_mois_method_id,
                                   &on_message_callback);

    //注册app状态回调
    app_->register_state_handler(&on_state_callback);
    //启动app
    app_->start();
    while(true){
        usleep(1000 * 1000);
    }
    return 1;
}
