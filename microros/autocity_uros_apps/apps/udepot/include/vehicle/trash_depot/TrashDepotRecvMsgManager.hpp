/*
 * @Author: hanson
 * @Date: 2024-12-09 16:18:27
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-13 17:24:16
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\trash_depot\TrashDepotRecvMsgManager.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_TRASHDEPOTRECVMSGMANAGER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_TRASHDEPOTRECVMSGMANAGER_HPP_

#include "msg_manager/RecvMsgManager.hpp"
#include "msg_wrap/TrashDepotStatusMsgWrap.hpp"
#include "sensor/RadarSensor.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            class TrashDepotRecvMsgManager : public RecvMsgManager<TrashDepotStatusMsgWrap>
            {
            private:
                /* data */
                RadarSensor _radar_sensor;

            public:
                TrashDepotRecvMsgManager(/* args */) = default;
                virtual ~TrashDepotRecvMsgManager() = default;

                int Setup() override;

                void UpdateChassis() override;

                void UpdateSensor() override;
            };
        }
    }
}

#endif // APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_TRASHDEPOTRECVMSGMANAGER_HPP_
