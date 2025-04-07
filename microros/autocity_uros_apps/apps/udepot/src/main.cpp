/*
 * @Author: hanson hanson@citygo.com.cn
 * @Date: 2024-08-20 15:42:39
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-02 15:58:41
 * @FilePath: \autocity_uros_apps\apps\udepot\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "trace/LogTrace.hpp"
#include "trace/BackTrace.hpp"
#include "param/ParamHelper.hpp"
#include "transport/Transport.hpp"
#include "vehicle/TransoprtHandlerHelper.hpp"

using namespace auto_city::udepot;

void main(void)
{
    LOG_INFO("udepot startup build time: %s %s\r\n", __DATE__, __TIME__);
    auto_city::BackTrace::SetUp();

    if (SingleTonParamHelper::Instance().LoadConfig() != 0)
    {
        LOG_FATAL("config load failed\r\n");
        return;
    }

    auto handler = SingleTonTransportHandlerHelper::Instance().CreateDataHandler();

    if (handler->Setup() != 0)
    {
        LOG_FATAL("handler Setup failed\r\n");
        return;
    }
    if (SingleTonTransport::Instance().Setup(handler) != 0)
    {
        LOG_FATAL("transport Setup failed\r\n");
        return;
    }
    // spin forever
    handler->Spin();
}
