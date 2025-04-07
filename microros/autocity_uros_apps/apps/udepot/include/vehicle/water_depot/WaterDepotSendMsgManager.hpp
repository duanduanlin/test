/*
 * @Author: hanson
 * @Date: 2024-10-15 14:04:10
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:33:26
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\water_depot\WaterDepotSendMsgManager.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_ECAR3SENDMSGMANAGER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_ECAR3SENDMSGMANAGER_HPP_

#include "msg_manager/SendMsgManager.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace water
        {
            class WaterDepotSendMsgManager : public SendMsgManager
            {
            private:
                /* data */
            public:
                WaterDepotSendMsgManager(/* args */);
                virtual ~WaterDepotSendMsgManager();

                int Setup() override;

                std::vector<can_frame> GetCanFrames() override;
            };

        }
    }
}

#endif // APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_ECAR3SENDMSGMANAGER_HPP_
