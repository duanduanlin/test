/*
 * @Author: hanson hanson@citygo.com.cn
 * @Date: 2024-08-20 15:42:39
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-29 11:28:49
 * @FilePath: \autocity_uros_apps\apps\ucanbus\src\main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "node/UcanbusNode.hpp"
#include "transport/Transport.hpp"
#include "vehicle/VehicleFactoryHelper.hpp"
#include "trace/LogTrace.hpp"
#include "trace/BackTrace.hpp"

void main(void)
{
    LOG_INFO("ucanbus startup build time: %s %s\r\n", __DATE__, __TIME__);
    BackTrace::SetUp();
    if (SingleTonParamHelper::Instance().LoadConfig() != 0)
    {
        LOG_FATAL("config load failed\r\n");
        return;
    }
    std::shared_ptr<UcanbusNode> ucanbus_node = std::make_shared<UcanbusNode>("ucanbus");
    if (ucanbus_node->Setup() < 0)
    {
        LOG_FATAL("ucanbus node Setup failed\r\n");
        return;
    }

    auto vehicle_factory = SingleTonVehicleFactoryHelper::Instance().CreateVehicleFactory();
    if (SingleTonTransport::Instance().Setup(ucanbus_node, vehicle_factory) != 0)
    {
        LOG_FATAL("transport Setup failed\r\n");
        return;
    }

    // spin forever
    ucanbus_node->Spin();
}
