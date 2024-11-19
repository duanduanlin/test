/*
 * @Author: hanson
 * @Date: 2024-08-27 11:41:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-11 10:31:07
 * @Description:
 * @FilePath: \ucanbus\src\vehicle\ecar3\Ecar3VehicleFactory.cpp
 */
#include "vehicle/ecar3/Ecar3VehicleFactory.hpp"
#include "vehicle/ecar3/Ecar3Cancard.hpp"
#include "vehicle/ecar3/Ecar3RecvMsgManager.hpp"
#include "vehicle/ecar3/Ecar3SendMsgManager.hpp"
#include "vehicle/ecar3/Ecar3VehicleController.hpp"
#include "trace/LogTrace.hpp"
#include "param/ParamHelper.hpp"

Ecar3VehicleFactory::Ecar3VehicleFactory(/* args */)
{
}

Ecar3VehicleFactory::~Ecar3VehicleFactory()
{
}

std::shared_ptr<BaseCancard> Ecar3VehicleFactory::CreateCancard()
{
    return std::make_shared<Ecar3Cancard>(GetParamWithDefault<std::string>("can_interfaces", "can1"));
}

std::shared_ptr<RecvMsgManager> Ecar3VehicleFactory::CreateRecvMsgManager()
{
    return std::make_shared<Ecar3RecvMsgManager>();
}

std::shared_ptr<SendMsgManager> Ecar3VehicleFactory::CreateSendMsgManager()
{
    return std::make_shared<Ecar3SendMsgManager>();
}

std::shared_ptr<BaseVehicleController> Ecar3VehicleFactory::CreateVehicleController()
{
    return std::make_shared<Ecar3VehicleController>();
}
