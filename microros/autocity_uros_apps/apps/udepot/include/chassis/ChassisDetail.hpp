/*
 * @Author: hanson
 * @Date: 2024-08-27 16:12:31
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 13:55:14
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\chassis\ChassisDetail.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_CHASSIS_CHASSISDETAIL_HPP_
#define APPS_UDEPOT_INCLUDE_CHASSIS_CHASSISDETAIL_HPP_

#include <memory>
#include "chassis/WaterDepotDetail.hpp"
#include "chassis/TrashDepotDetail.hpp"
namespace auto_city
{
    namespace udepot
    {
        class ChassisDetail
        {
        private:
            /* data */
            std::shared_ptr<WaterDepotDetail> _water_depot_chassis = std::make_shared<WaterDepotDetail>();
            std::shared_ptr<TrashDepotDetail> _trash_depot_chassis = std::make_shared<TrashDepotDetail>();

        public:
            ChassisDetail(/* args */) = default;
            ~ChassisDetail() = default;

            std::shared_ptr<WaterDepotDetail> GetWaterDepotChassis() const
            {
                return _water_depot_chassis;
            }

            std::shared_ptr<TrashDepotDetail> GetTrashDepotChassis() const
            {
                return _trash_depot_chassis;
            }
        };
    }
}

#endif // APPS_UDEPOT_INCLUDE_CHASSIS_CHASSISDETAIL_HPP_
