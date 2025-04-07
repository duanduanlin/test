/*
 * @Author: hanson
 * @Date: 2024-08-27 11:26:37
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:25:00
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\trash_depot\TrashDepotCancard.hpp
 */
#ifndef INCLUDE_VEHICLE_WATER_DEPOT_TRASHDEPOTCANCARD_HPP_
#define INCLUDE_VEHICLE_WATER_DEPOT_TRASHDEPOTCANCARD_HPP_

#include "cancard/BaseCancard.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            class TrashDepotCancard : public BaseCancard
            {
            private:
                /* data */
            public:
                TrashDepotCancard(const std::string name);
                virtual ~TrashDepotCancard();

                int CanSend(std::vector<can_frame> &frames) override;
                int CanSend(can_frame &frame) override;

                int CanRecv(can_frame &aframe) override;
            };
        }
    }
}
#endif // INCLUDE_VEHICLE_WATER_DEPOT_TRASHDEPOTCANCARD_HPP_
