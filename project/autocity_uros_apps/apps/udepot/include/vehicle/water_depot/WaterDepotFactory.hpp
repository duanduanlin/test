/*
 * @Author: hanson
 * @Date: 2024-08-27 11:40:38
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 14:26:18
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\water_depot\WaterDepotFactory.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_ECAR3VEHICLEFACTORY_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_ECAR3VEHICLEFACTORY_HPP_

#include "vehicle/BaseVehicleFactory.hpp"

class WaterDepotFactory : public BaseVehicleFactory
{
private:
    /* data */
public:
    WaterDepotFactory(/* args */);
    virtual ~WaterDepotFactory();

    std::shared_ptr<BaseCancard> CreateCancard() override;
    std::shared_ptr<RecvMsgManager> CreateRecvMsgManager() override;
    std::shared_ptr<SendMsgManager> CreateSendMsgManager() override;
    std::shared_ptr<BaseVehicleController> CreateVehicleController() override;
};

#endif // APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_ECAR3VEHICLEFACTORY_HPP_
