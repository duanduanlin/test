#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTRECVMSGMANAGER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTRECVMSGMANAGER_HPP_

#include "msg_manager/RecvMsgManager.hpp"
#include "msg_wrap/WaterDepotStatusMsgWrap.hpp"
#include "sensor/FlowSensor.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace water
        {
            class WaterDepotRecvMsgManager : public RecvMsgManager<WaterDepotStatusMsgWrap>
            {
            private:
                /* data */
                FlowSensor _flow_sensor;

            public:
                WaterDepotRecvMsgManager(/* args */) = default;
                virtual ~WaterDepotRecvMsgManager() = default;

                int Setup() override;

                void UpdateChassis() override;

                void UpdateSensor() override;
            };
        }
    }
}

#endif // APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTRECVMSGMANAGER_HPP_
