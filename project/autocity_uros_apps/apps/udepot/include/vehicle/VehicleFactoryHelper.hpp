/*
 * @Author: hanson
 * @Date: 2024-08-27 11:48:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 10:05:03
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\VehicleFactoryHelper.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_VEHICLEFACTORYHELPER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_VEHICLEFACTORYHELPER_HPP_

#include "vehicle/BaseVehicleFactory.hpp"
#include "vehicle/water_depot/WaterDepotFactory.hpp"
#include "common/Singleton.hpp"
#include "param/ParamHelper.hpp"

class VehicleFactoryHelper
{
private:
    /* data */
public:
    VehicleFactoryHelper(/* args */) = default;
    virtual ~VehicleFactoryHelper() = default;

    std::shared_ptr<BaseVehicleFactory> CreateVehicleFactory()
    {
        if (GetParamWithDefault<std::string>("vehicle_name", "none") == "WaterDepot")
        {
            return std::make_shared<WaterDepotFactory>();
        }
        else
        {
            return nullptr;
        }
    }
};
using SingleTonVehicleFactoryHelper = Singleton<VehicleFactoryHelper>;
#endif // APPS_UDEPOT_INCLUDE_VEHICLE_VEHICLEFACTORYHELPER_HPP_
