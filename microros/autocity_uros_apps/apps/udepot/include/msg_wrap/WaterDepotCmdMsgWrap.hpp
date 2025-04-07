/*
 * @Author: hanson
 * @Date: 2024-08-23 14:29:06
 * @LastEditors: hanson
 * @LastEditTime: 2024-11-29 10:17:01
 * @Description:
 * @FilePath: \autocity_uros_apps\apps\udepot\include\msg_wrap\WaterDepotCmdMsgWrap.hpp
 */

#ifndef APPS_UDEPOT_INCLUDE_MSG_WRAP_WATERDEPOTCMDMSGWRAP_HPP_
#define APPS_UDEPOT_INCLUDE_MSG_WRAP_WATERDEPOTCMDMSGWRAP_HPP_

#include <udepot_cmd_msgs/msg/water_depot_cmd.h>
#include "msg_wrap/BaseMsgWrap.hpp"

namespace auto_city
{
    namespace udepot
    {
#define WaterDepotCmdMsgType (ROSIDL_GET_MSG_TYPE_SUPPORT(udepot_cmd_msgs, msg, WaterDepotCmd))
        using WaterDepotCmdMsg = udepot_cmd_msgs__msg__WaterDepotCmd;

        class WaterDepotCmdMsgWrap : public BaseMsgWrap<WaterDepotCmdMsg>
        {
        private:
            /* water depot cmd */
            WaterDepotCmdMsg _water_depot_cmd;

        public:
            WaterDepotCmdMsgWrap(/* args */);
            ~WaterDepotCmdMsgWrap();

            void Setup() override;
            void Update() override;
            void Reset() override;

            std::string GetPrintableStr() override;

            WaterDepotCmdMsg &GetWaterDepotCmd()
            {
                return _water_depot_cmd;
            }
        };
    }
}
#endif // APPS_UDEPOT_INCLUDE_MSG_WRAP_WATERDEPOTCMDMSGWRAP_HPP_
