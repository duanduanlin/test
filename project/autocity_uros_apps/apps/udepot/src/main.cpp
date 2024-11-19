/*
 * @Author: hanson hanson@citygo.com.cn
 * @Date: 2024-08-20 15:42:39
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-13 16:36:26
 * @FilePath: \autocity_uros_apps\apps\udepot\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "node/UdepotNode.hpp"
#include "trace/LogTrace.hpp"
#include "trace/BackTrace.hpp"
#include "param/ParamHelper.hpp"
#include "transport/Transport.hpp"
#include "vehicle/VehicleFactoryHelper.hpp"

void main(void)
{
    LOG_INFO("udepot startup build time: %s %s\r\n", __DATE__, __TIME__);
    BackTrace::SetUp();

    if (SingleTonParamHelper::Instance().LoadConfig() != 0)
    {
        LOG_FATAL("config load failed\r\n");
        return;
    }

    std::shared_ptr<UdepotNode> node = std::make_shared<UdepotNode>("udepot");
    if (node->Setup() < 0)
    {
        LOG_FATAL("udepot node Setup failed\r\n");
        return;
    }

    auto vehicle_factory = SingleTonVehicleFactoryHelper::Instance().CreateVehicleFactory();
    if (SingleTonTransport::Instance().Setup(node, vehicle_factory) != 0)
    {
        LOG_FATAL("transport Setup failed\r\n");
        return;
    }

    // spin forever
    node->Spin();
}
