/*
 * @Author: hanson
 * @Date: 2024-08-27 16:12:31
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 10:52:08
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\chassis\ChassisDetail.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_CHASSIS_CHASSISDETAIL_HPP_
#define APPS_UDEPOT_INCLUDE_CHASSIS_CHASSISDETAIL_HPP_

#include <memory>
#include "chassis/WaterDepotDetail.hpp"

class ChassisDetail
{
private:
    /* data */
    std::shared_ptr<WaterDepotDetail> _water_depot_chassis = std::make_shared<WaterDepotDetail>();

public:
    ChassisDetail(/* args */) = default;
    ~ChassisDetail() = default;

    std::shared_ptr<WaterDepotDetail> GetWaterDepotChassis() const
    {
        return _water_depot_chassis;
    }
};

#endif // APPS_UDEPOT_INCLUDE_CHASSIS_CHASSISDETAIL_HPP_
