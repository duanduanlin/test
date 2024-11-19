/*
 * @Author: hanson
 * @Date: 2024-08-27 11:41:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 14:18:07
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\src\vehicle\water_depot\WaterDepotFactory.cpp
 */
#include "vehicle/water_depot/WaterDepotFactory.hpp"
#include "vehicle/water_depot/WaterDepotCancard.hpp"
#include "vehicle/water_depot/WaterDepotRecvMsgManager.hpp"
#include "vehicle/water_depot/WaterDepotSendMsgManager.hpp"
#include "vehicle/water_depot/WaterDepotController.hpp"
#include "trace/LogTrace.hpp"
#include "param/ParamHelper.hpp"

WaterDepotFactory::WaterDepotFactory(/* args */)
{
}

WaterDepotFactory::~WaterDepotFactory()
{
}

std::shared_ptr<BaseCancard> WaterDepotFactory::CreateCancard()
{
    return std::make_shared<WaterDepotCancard>(GetParamWithDefault<std::string>("can_interfaces", "can1"));
}

std::shared_ptr<RecvMsgManager> WaterDepotFactory::CreateRecvMsgManager()
{
    return std::make_shared<WaterDepotRecvMsgManager>();
}

std::shared_ptr<SendMsgManager> WaterDepotFactory::CreateSendMsgManager()
{
    return std::make_shared<WaterDepotSendMsgManager>();
}

std::shared_ptr<BaseVehicleController> WaterDepotFactory::CreateVehicleController()
{
    return std::make_shared<WaterDepotController>();
}
