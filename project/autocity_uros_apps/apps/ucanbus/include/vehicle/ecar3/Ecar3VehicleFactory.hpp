/*
 * @Author: hanson
 * @Date: 2024-08-27 11:40:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-08-28 16:05:31
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\ecar3\Ecar3VehicleFactory.hpp
 */
#ifndef INCLUDE_VEHICLE_ECAR3_ECAR3VEHICLEFACTORY_HPP_
#define INCLUDE_VEHICLE_ECAR3_ECAR3VEHICLEFACTORY_HPP_

#include "vehicle/BaseVehicleFactory.hpp"

class Ecar3VehicleFactory : public BaseVehicleFactory
{
private:
    /* data */
public:
    Ecar3VehicleFactory(/* args */);
    virtual ~Ecar3VehicleFactory();

    std::shared_ptr<BaseCancard> CreateCancard() override;
    std::shared_ptr<RecvMsgManager> CreateRecvMsgManager() override;
    std::shared_ptr<SendMsgManager> CreateSendMsgManager() override;
    std::shared_ptr<BaseVehicleController> CreateVehicleController() override;
};

#endif // INCLUDE_VEHICLE_ECAR3_ECAR3VEHICLEFACTORY_HPP_
