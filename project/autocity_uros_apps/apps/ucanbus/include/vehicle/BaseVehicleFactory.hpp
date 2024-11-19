/*
 * @Author: hanson
 * @Date: 2024-08-27 11:30:35
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-28 16:01:16
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\BaseVehicleFactory.hpp
 */
#ifndef INCLUDE_VEHICLE_BASEVEHICLEFACTORY_HPP_
#define INCLUDE_VEHICLE_BASEVEHICLEFACTORY_HPP_

#include <memory>
#include "cancard/BaseCancard.hpp"
#include "msg_manager/RecvMsgManager.hpp"
#include "msg_manager/SendMsgManager.hpp"
#include "vehicle/BaseVehicleController.hpp"

class BaseVehicleFactory
{
private:
    /* data */
public:
    BaseVehicleFactory() = default;
    virtual ~BaseVehicleFactory() = default;

    virtual std::shared_ptr<BaseCancard> CreateCancard() = 0;
    virtual std::shared_ptr<RecvMsgManager> CreateRecvMsgManager() = 0;
    virtual std::shared_ptr<SendMsgManager> CreateSendMsgManager() = 0;
    virtual std::shared_ptr<BaseVehicleController> CreateVehicleController() = 0;
};

#endif // INCLUDE_VEHICLE_BASEVEHICLEFACTORY_HPP_
