/*
 * @Author: hanson
 * @Date: 2024-10-15 14:04:10
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:27:09
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\vehicle\trash_depot\TrashDepotSendMsgManager.hpp
 */
#ifndef APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_SENDMSGMANAGER_HPP_
#define APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_SENDMSGMANAGER_HPP_

#include "msg_manager/SendMsgManager.hpp"

namespace auto_city
{
    namespace udepot
    {
        namespace trash
        {
            class TrashDepotSendMsgManager : public SendMsgManager
            {
            private:
                /* data */
            public:
                TrashDepotSendMsgManager(/* args */);
                virtual ~TrashDepotSendMsgManager();

                int Setup() override;

                std::vector<can_frame> GetCanFrames() override;
            };
        }
    }
}

#endif // APPS_UDEPOT_INCLUDE_VEHICLE_TRASH_DEPOT_SENDMSGMANAGER_HPP_
