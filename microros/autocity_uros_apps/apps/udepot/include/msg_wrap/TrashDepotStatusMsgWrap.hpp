/*
 * @Author: hanson
 * @Date: 2024-08-23 10:35:59
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-28 17:40:08
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\msg_wrap\TrashDepotStatusMsgWrap.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_MSG_WRAP_TRASHDEPOTSTATUSMSGWRAP_HPP_
#define APPS_UDEPOT_INCLUDE_MSG_WRAP_TRASHDEPOTSTATUSMSGWRAP_HPP_

#include <udepot_status_msgs/msg/trash_depot_status.h>
#include "msg_wrap/BaseMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
#define TrashDepotStatusMsgType (ROSIDL_GET_MSG_TYPE_SUPPORT(udepot_status_msgs, msg, TrashDepotStatus))
        using TrashDepotStatusMsg = udepot_status_msgs__msg__TrashDepotStatus;
        class TrashDepotStatusMsgWrap : public BaseMsgWrap<TrashDepotStatusMsg>
        {

        private:
            /* data */

        public:
            TrashDepotStatusMsgWrap(/* args */);
            ~TrashDepotStatusMsgWrap();

            void Setup() override;
            void Update() override;
            void Reset() override;

            std::string GetPrintableStr() override;
        };
    }
}
#endif // APPS_UDEPOT_INCLUDE_MSG_WRAP_TRASHDEPOTSTATUSMSGWRAP_HPP_
