/*
 * @Author: hanson
 * @Date: 2024-08-23 14:29:06
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:22:00
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\msg_wrap\TrashDepotCmdMsgWrap.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_MSG_WRAP_TRASHDEPOTCMDMSGWRAP_HPP_
#define APPS_UDEPOT_INCLUDE_MSG_WRAP_TRASHDEPOTCMDMSGWRAP_HPP_

#include <udepot_cmd_msgs/msg/trash_depot_cmd.h>
#include "msg_wrap/BaseMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
#define TrashDepotCmdMsgType (ROSIDL_GET_MSG_TYPE_SUPPORT(udepot_cmd_msgs, msg, TrashDepotCmd))
        using TrashDepotCmdMsg = udepot_cmd_msgs__msg__TrashDepotCmd;

        class TrashDepotCmdMsgWrap : public BaseMsgWrap<TrashDepotCmdMsg>
        {
        private:
            /* water depot cmd */
            TrashDepotCmdMsg _trash_depot_cmd;

        public:
            TrashDepotCmdMsgWrap(/* args */);
            ~TrashDepotCmdMsgWrap();

            void Setup() override;
            void Update() override;
            void Reset() override;

            std::string GetPrintableStr() override;

            TrashDepotCmdMsg &GetTrashDepotCmd()
            {
                return _trash_depot_cmd;
            }
        };
    }
}
#endif // APPS_UDEPOT_INCLUDE_MSG_WRAP_TRASHDEPOTCMDMSGWRAP_HPP_
