/*
 * @Author: hanson
 * @Date: 2024-08-27 11:48:47
 * @LastEditors: hanson
 * @LastEditTime: 2024-09-11 11:49:31
 * @Description:
 * @FilePath: \ucanbus\include\vehicle\VehicleFactoryHelper.hpp
 */
#ifndef INCLUDE_VEHICLE_VEHICLEFACTORYHELPER_HPP_
#define INCLUDE_VEHICLE_VEHICLEFACTORYHELPER_HPP_

#include "vehicle/BaseVehicleFactory.hpp"
#include "vehicle/ecar3/Ecar3VehicleFactory.hpp"
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
        if (GetParamWithDefault<std::string>("vehicle_name", "none") == "EcarThreeWheel")
        {
            return std::make_shared<Ecar3VehicleFactory>();
        }
        else
        {
            return nullptr;
        }
    }
};
using SingleTonVehicleFactoryHelper = Singleton<VehicleFactoryHelper>;
#endif // INCLUDE_VEHICLE_VEHICLEFACTORYHELPER_HPP_
