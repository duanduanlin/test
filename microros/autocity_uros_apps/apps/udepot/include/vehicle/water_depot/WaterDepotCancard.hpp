/*
 * @Author: hanson
 * @Date: 2024-08-27 11:26:37
 * @LastEditors: hanson
 * @LastEditTime: 2024-10-15 10:06:07
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\water_depot\WaterDepotCancard.hpp
 */
#ifndef INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTCANCARD_HPP_
#define INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTCANCARD_HPP_

#include "cancard/BaseCancard.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace water
        {
            class WaterDepotCancard : public BaseCancard
            {
            private:
                /* data */
            public:
                WaterDepotCancard(const std::string name);
                virtual ~WaterDepotCancard();

                int CanSend(std::vector<can_frame> &frames) override;
                int CanSend(can_frame &frame) override;

                int CanRecv(can_frame &aframe) override;
            };
        }
    }
}
#endif // INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTCANCARD_HPP_
