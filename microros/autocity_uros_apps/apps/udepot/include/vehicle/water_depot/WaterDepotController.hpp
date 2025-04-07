/*
 * @Author: hanson
 * @Date: 2024-08-28 15:55:50
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-28 18:30:22
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\water_depot\WaterDepotController.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTCONTROLLER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTCONTROLLER_HPP_

#include "vehicle/BaseVehicleController.hpp"
#include "common/TimeTools.hpp"
#include "vehicle/water_depot/protocol/CANIO101.hpp"
#include "vehicle/water_depot/protocol/CANIO201.hpp"
#include "msg_wrap/WaterDepotCmdMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace water
        {
            class WaterDepotController : public BaseVehicleController<WaterDepotCmdMsgWrap>
            {
            private:
                /* data */
                /*chassis cmd */
                CANIO101 *_writeIO_101 = nullptr;
                CANIO201 *_readIO_201 = nullptr;
                /*task time*/

            public:
                WaterDepotController(/* args */) = default;
                virtual ~WaterDepotController() = default;

                int Setup(std::unordered_map<uint32_t, BaseProtocol *> &protocol_map, WaterDepotCmdMsgWrap *msg, ChassisDetail *chassis) override;
                int UpdateControlCmd() override;

            private:
            };
        }
    }
}

#endif // APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTCONTROLLER_HPP_
