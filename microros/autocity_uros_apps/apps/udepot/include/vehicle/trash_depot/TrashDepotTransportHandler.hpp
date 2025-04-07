/*
 * @Author: hanson
 * @Date: 2024-11-28 16:21:15
 * @LastEditors: hanson
 * @LastEditTime: 2024-12-02 16:22:37
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\trash_depot\TrashDepotTransportHandler.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_TRASHDEPOTTRANSPORTHANDLER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_TRASHDEPOTTRANSPORTHANDLER_HPP_

#include "vehicle/BaseTransportHandler.hpp"
#include "vehicle/trash_depot/TrashDepotNode.hpp"
#include "vehicle/trash_depot/TrashDepotController.hpp"
#include "vehicle/trash_depot/TrashDepotRecvMsgManager.hpp"
#include "vehicle/trash_depot/TrashDepotCancard.hpp"
#include "vehicle/trash_depot/TrashDepotSendMsgManager.hpp"
namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            class TrashDepotTransportHandler : public BaseTransportHandler
            {
            private:
                /* data */
                std::shared_ptr<TrashDepotNode> _node;
                std::shared_ptr<TrashDepotController> _vehicle_controller;
                std::shared_ptr<TrashDepotRecvMsgManager> _recv_msg_manager;

            public:
                TrashDepotTransportHandler(/* args */) = default;
                ~TrashDepotTransportHandler() = default;

                void Spin() override;

                int Setup() override;
                int HandleRecvData() override;
                int HandleSendData() override;
                int HandlePubMsg() override;
            };
        }
    }
}
#endif // APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_TRASHDEPOTTRANSPORTHANDLER_HPP_
