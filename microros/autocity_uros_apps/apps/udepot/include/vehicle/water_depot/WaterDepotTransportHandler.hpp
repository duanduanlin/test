/*
 * @Author: hanson
 * @Date: 2024-11-28 11:13:55
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-02 16:23:18
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\water_depot\WaterDepotTransportHandler.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTTRANSPORTHANDLER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTTRANSPORTHANDLER_HPP_

#include "vehicle/BaseTransportHandler.hpp"
#include "vehicle/water_depot/WaterDepotNode.hpp"
#include "vehicle/water_depot/WaterDepotController.hpp"
#include "vehicle/water_depot/WaterDepotRecvMsgManager.hpp"
#include "vehicle/water_depot/WaterDepotCancard.hpp"
#include "vehicle/water_depot/WaterDepotSendMsgManager.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace water
        {
            class WaterDepotTransportHandler : public BaseTransportHandler
            {
            private:
                /* data */
                std::shared_ptr<WaterDepotNode> _node;
                std::shared_ptr<WaterDepotController> _vehicle_controller;
                std::shared_ptr<WaterDepotRecvMsgManager> _recv_msg_manager;

            public:
                WaterDepotTransportHandler(/* args */) = default;
                ~WaterDepotTransportHandler() = default;

                void Spin() override;

                int Setup() override;
                int HandleRecvData() override;
                int HandleSendData() override;
                int HandlePubMsg() override;
            };
        }
    }
}
#endif // APPS_UDEPOT_INCLUDE_VEHICLE_WATER_DEPOT_WATERDEPOTTRANSPORTHANDLER_HPP_
